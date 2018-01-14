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

extern plist fd_list;

int get_function_size(ptree t){
    assert(t);
    switch(t->code){
        // 'sizeless' nodes
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_VAR :
        case T_APP :
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

ptree apply_inline_expansion(ptree t){
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        pfundef fd = (pfundef)l_node->data;
        printf("size of %s : %d\n", fd->var, get_function_size(fd->body));
        if ((get_function_size(fd->body) <= INLINE_THRESHOLD) &&
            (fd->free_vars->head == NULL)){
                printf("replacing %s\n", fd->var);
            t = replace_funcall_by_body(fd, t);
        }
        l_node = l_node->next;
    }
    // applying inline expansion can nest let
    return reduce_nested_let(t);
}

ptree replace_funcall_by_body(pfundef fd, ptree t){
    assert(fd && t);
    listNode *l_node, *l_node_fd, *l_node_call;
    env_node *env;
    char *var_name;
    plist args_remaining;
    switch(t->code){
        // function call -> the interesting part
        case T_APP :
            if((t->params.tapp.t->code == T_VAR) &&
                (strcmp(t->params.tapp.t->params.v, fd->var) == 0)){
                env = NULL;
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
                    return alpha_convert(fd->body, env);
                } else { // there are args remaining
                    var_name = gen_varname();
                    args_remaining = empty();
                    args_remaining->head = l_node_call;
                    args_remaining->logicalLength =
                        t->params.tapp.l->logicalLength -
                        fd->args->logicalLength;
                    return ast_let(
                        var_name,
                        alpha_convert(fd->body, env),
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
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            t->params.tbinary.t1 =
                replace_funcall_by_body(fd, t->params.tbinary.t1);
            t->params.tbinary.t1 =
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
