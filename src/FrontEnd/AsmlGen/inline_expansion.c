#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "inline_expansion.h"
#include "list.h"
#include "ast.h"
#include "utils.h"
#include "alpha_conv.h"
#include "reduce_nested_let.h"
#include "duplicate.h"

extern plist fd_list;

ptree apply_inline_expansion(ptree t){
    t = duplicate_tree(t);
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        pfundef fd = (pfundef)l_node->data;
        if ((get_function_size(fd->body) <= INLINE_THRESHOLD) &&
        (fd->free_vars->head == NULL) &&
        (!is_used_as_var(fd, t)) &&
        !is_used_in_other_fd_bodies(fd)){
            t = replace_funcall_by_body(fd, t);
            remove_fd_from_fd_list(fd);
        }
        l_node = l_node->next;
    }
    // applying inline expansion can nest let
    return reduce_nested_let(t);
}

int get_function_size(ptree t){
    assert(t);
    switch(t->code){
        // 'sizeless' nodes
        case T_VAR :
            if (is_a_label(t->params.v)){
                pfundef fd = get_fd(t->params.v);
                if (fd->free_vars != NULL){
                    return INLINE_THRESHOLD + 1;
                }
            } else {
                return 0;
            }

        case T_APP :
            if ((t->params.tapp.t->code == T_VAR) &&
                is_a_label(t->params.tapp.t->params.v)){
                pfundef fd = get_fd(t->params.tapp.t->params.v);
                if ((fd != NULL) && (fd->free_vars != NULL)){
                    return INLINE_THRESHOLD + 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_TUPLE :
        case T_NOT :
        case T_NEG :
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
            return 0;

        // 'nodes with a size'
        case T_IF :
            return get_function_size(t->params.tternary.t2) +
                get_function_size(t->params.tternary.t3) + 1;

        case T_LET :
            return get_function_size(t->params.tlet.t1) +
                get_function_size(t->params.tlet.t2) + 1;

        case T_LETTUPLE :
            return get_function_size(t->params.lettuple.t1) +
                get_function_size(t->params.lettuple.t2) + 1;

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            fprintf(stderr, "TBI : get_function_size, code = %d not implem yet.\n"
            "Exiting.\n", t->code);
            exit(1);

        // Error
        case T_LETREC :
        default :
            fprintf(stderr, "Error : get_function_size, code ="
            " %d (incorrect).\nExiting.\n", t->code);
            exit(1);
    }
}


ptree replace_funcall_by_body(pfundef fd, ptree t){
    assert(fd && t);
    listNode *l_node, *l_node_fd, *l_node_call;
    env_node *env;
    char *var_name;
    ptree tmp;
    plist args_remaining;
    switch(t->code){
        // function call -> the interesting part
        case T_APP :
            // if function called is the one to replace
            if((t->params.tapp.t->code == T_VAR) &&
                (strcmp(t->params.tapp.t->params.v, fd->var) == 0)){
                env = init_env();
                l_node_call = t->params.tapp.l->head;
                l_node_fd = fd->args->head;
                while(l_node_fd != NULL){
                    assert(((ptree)l_node_call->data)->code == T_VAR);
                    env = gen_env_node(
                        (char *)l_node_fd->data,
                        (char *)((ptree)l_node_call->data)->params.v,
                        env
                    );
                    l_node_fd = l_node_fd->next;
                    l_node_call = l_node_call->next;
                }
                // all the args from the call have been consumed by the function
                if (l_node_call == NULL){
                    tmp = alpha_convert(duplicate_tree(fd->body), env);
                    return tmp;
                } else { // there are args remaining
                    var_name = gen_varname();
                    args_remaining = empty();
                    args_remaining->head = l_node_call;
                    args_remaining->logicalLength =
                        t->params.tapp.l->logicalLength -
                        fd->args->logicalLength;
                    return ast_let(
                        var_name,
                        alpha_convert(duplicate_tree(fd->body), env),
                        ast_app(
                            ast_var(var_name),
                            args_remaining
                        )
                    );
                }
            } else {
                t->params.tapp.t =
                    replace_funcall_by_body(fd, t->params.tapp.t);
                return t;
            }

        //now the rest, i.e recursive calls
        // leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_VAR :
            return t;

        // unary nodes
        case T_NOT :
        case T_NEG :
            t->params.t = replace_funcall_by_body(fd, t->params.t);
            return t;

        // binary nodes
        case T_ADD :
            t->params.tbinary.t1 =
                replace_funcall_by_body(fd, t->params.tbinary.t1);
            t->params.tbinary.t2 =
                replace_funcall_by_body(fd, t->params.tbinary.t2);
            return t;
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            t->params.tbinary.t1 =
                replace_funcall_by_body(fd, t->params.tbinary.t1);
            t->params.tbinary.t2 =
                replace_funcall_by_body(fd, t->params.tbinary.t2);
            return t;

        // ternary nodes
        case T_IF :
        case T_PUT :
            t->params.tternary.t1 =
                replace_funcall_by_body(fd, t->params.tternary.t1);
            t->params.tternary.t2 =
                replace_funcall_by_body(fd, t->params.tternary.t2);
            t->params.tternary.t3 =
                replace_funcall_by_body(fd, t->params.tternary.t3);
            return t;

        // other cases
        case T_LET :
            t->params.tlet.t1 =
                replace_funcall_by_body(fd, t->params.tlet.t1);
            t->params.tlet.t2 =
                replace_funcall_by_body(fd, t->params.tlet.t2);
            return t;

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                l_node->data = replace_funcall_by_body(fd, (ptree)l_node->data);
                l_node = l_node->next;
            }
            return t;

        case T_LETTUPLE :
            t->params.lettuple.t1 =
                replace_funcall_by_body(fd, t->params.lettuple.t1);
            t->params.lettuple.t1 =
                replace_funcall_by_body(fd, t->params.lettuple.t1);
            return t;

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            fprintf(stderr, "TBI : get_function_size, code = %d not implem yet.\n"
            "Exiting.\n", t->code);
            exit(1);

        // Error
        case T_LETREC :
        default :
            fprintf(stderr, "Error : get_function_size, code ="
            " %d (incorrect).\nExiting.\n", t->code);
            exit(1);
    }
}

void remove_fd_from_fd_list(pfundef fd){
    listNode *current = fd_list->head, *next = current->next;
    if (strcmp(fd->var, ((pfundef)current->data)->var) == 0){
        fd_list->head = fd_list->head->next;
        fd_list->logicalLength --;
    } else {
        while(next != NULL){
            if (strcmp(fd->var, ((pfundef)next->data)->var) == 0){
                current->next = next->next;
                fd_list->logicalLength --;
                return;
            }
            current = next;
            next = next->next;
        }
    }
}

bool is_used_as_var(pfundef fd, ptree t){
    assert(fd);
    assert(t);
    listNode *l_node;
    switch(t->code){
        // function  call -> check if var_name is one of the arguments
        case T_APP :
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                assert(((ptree)l_node->data)->code == T_VAR);
                if(strcmp(fd->var, ((ptree)l_node->data)->params.v) == 0){
                    return true;
                }
                l_node = l_node->next;
            }
            return false;

        case T_MK_CLOS :
        case T_APP_CLOS :
            l_node = t->params.tclosure.l->head;
            while(l_node != NULL){
                if(strcmp(fd->var, (char *)l_node->data) == 0){
                    return true;
                }
                l_node = l_node->next;
            }
            return false;

        //leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
            return false;

        case T_VAR :
            if (strcmp(fd->var, t->params.v) == 0){
                return true;
            }
            return false;

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                assert(((ptree)l_node->data)->code == T_VAR);
                if(strcmp(fd->var, ((ptree)l_node->data)->params.v) == 0){
                    return true;
                }
                l_node = l_node->next;
            }
            return false;

        // unary
        case T_NOT :
        case T_NEG :
            return is_used_as_var(fd, t->params.t);

        // binary
        case T_ADD :
        case T_SUB :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            return (
                is_used_as_var(fd, t->params.tbinary.t1) ||
                is_used_as_var(fd, t->params.tbinary.t2)
            );

        // ternary
        case T_IF :
        case T_PUT :
            return (
                is_used_as_var(fd, t->params.tternary.t1) ||
                is_used_as_var(fd, t->params.tternary.t2) ||
                is_used_as_var(fd, t->params.tternary.t3)
            );

        // other cases
        case T_LET :
            return (
                is_used_as_var(fd, t->params.tlet.t1) ||
                is_used_as_var(fd, t->params.tlet.t2)
            );

        case T_LETREC :
            return (
                is_used_as_var(fd, t->params.tletrec.fd->body) ||
                is_used_as_var(fd, t->params.tletrec.t)
            );

        case T_LETTUPLE :
            return (
                is_used_as_var(fd, t->params.lettuple.t1) ||
                is_used_as_var(fd, t->params.lettuple.t2)
            );

        default :
            fprintf(stderr, "TBI : in is_used_as_var, code %d not yet implemented.\n"
                "Exiting.\n", t->code);
            exit(1);
    }
}

bool is_used_in_other_fd_bodies(pfundef fd){
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        pfundef current_fd = (pfundef)l_node->data;
        if (is_used_as_var(fd, current_fd->body)){
            return true;
        }
        l_node = l_node->next;
    }
    return false;
}
