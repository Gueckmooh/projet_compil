#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "list.h"
#include "env.h"
#include "closure.h"
#include "utils.h"
#include "reduce_nested_let.h"
#include "knorm.h"
#include "duplicate.h"
#include "ast_to_asmlt.h"

extern plist fd_list;

ptree apply_closure_conversion(ptree t){
    // first apply closure conversion to function bodies
    listNode *l_node = fd_list->head;
    pfundef fd;
    while (l_node != NULL) {
        fd = (pfundef)l_node->data;

        // check that the function does not return a label
        fd->body = never_return_label(fd->body);
        l_node = l_node->next;

        // and now apply closure for real
        fd->body = apply_clos(fd->body);
        if (fd->free_vars != NULL){
            fd->body = add_free_vars_refs(fd, fd->free_vars->head, 1);

        // finally apply some basic transformations to it
        fd->body = reduce_nested_let(knorm(fd->body));
        }
    }
    // now apply closure conversion to the program itself;
    return apply_clos(t);
}

ptree apply_clos(ptree t){
    assert(t);
    if (t->code == T_APP){
        assert(t->params.tapp.t->code == T_VAR);
        // case -> func_name is a label
        if (is_a_label(t->params.tapp.t->params.v)){
            // find the fd in fd_list
            pfundef fd = get_fd(t->params.tapp.t->params.v);
            // case -> call to external function -> do nothing
            if(!fd){
                return t;
            }
            // case -> call with not enough args
            if (t->params.tapp.l->logicalLength < fd->args->logicalLength){
                // create a new function
                pfundef new_fd = alloc_fd();
                new_fd->var = gen_funcname();
                new_fd->args = empty();
                new_fd->free_vars = empty();
                // separate args in free_vars then args
                listNode *l_node = fd->args->head;
                int i = 0;
                while (i < t->params.tapp.l->logicalLength){
                    new_fd->free_vars = (
                        new_fd->free_vars->head == NULL ?
                        cons(l_node->data, empty()) :
                        append(new_fd->free_vars, cons(l_node->data, empty()))
                    );
                    l_node = l_node->next;
                    i ++;
                }
                while (l_node != NULL){
                    new_fd->args = (
                        new_fd->args->head == NULL ?
                        cons(l_node->data, empty()) :
                        append(new_fd->args, cons(l_node->data, empty()))
                    );
                    l_node = l_node->next;
                }
                // duplicate the body from fd
                new_fd->body = duplicate_tree(fd->body);
                // add the free vars refs
                new_fd->body = add_free_vars_refs(new_fd, new_fd->free_vars->head, WORD_SIZE);
                // add the new fd to fd_list
                fd_list = cons((void *)new_fd, fd_list);
                // prepare the make closure and return it
                char *new_var = gen_varname();
                plist mk_clos_args = cons(new_fd->var, empty());
                l_node = t->params.tapp.l->head;
                while (l_node != NULL){
                    ptree tmp = (ptree)l_node->data;
                    assert(tmp->code == T_VAR);
                    mk_clos_args = append(
                        mk_clos_args,
                        cons((char *)tmp->params.v, empty())
                    );
                    l_node = l_node->next;
                }
                return ast_let(
                    new_var,
                    ast_mkclos(mk_clos_args),
                    ast_var(new_var)
                );
            }
            // case -> function has no free vars -> leave it as is
            if (fd->free_vars->head == NULL){
                return t;
            // case -> function has free vars -> convert to make closure
            } else {
                char *new_varname = gen_varname();
                plist mk_clos_args = append(
                    cons(fd->var, empty()),
                    empty()
                );
                listNode *l_node = fd->free_vars->head;
                while(l_node != NULL){
                    // ptree tmp = l_node->data;
                    // assert(tmp->code == T_VAR);
                    // mk_clos_args = append(
                    //     mk_clos_args,
                    //     cons(tmp->params.v, empty())
                    // );
                    mk_clos_args = append(
                        mk_clos_args,
                        cons(l_node->data, empty())
                    );
                    l_node = l_node->next;
                }
                plist app_clos_args = cons(new_varname, empty());
                l_node = t->params.tapp.l->head;
                while(l_node != NULL){
                    ptree tmp = (ptree)l_node->data;
                    assert(tmp->code == T_VAR);
                    app_clos_args = append(
                        app_clos_args,
                        cons((char *)tmp->params.v, empty())
                    );
                    l_node = l_node->next;
                }
                return ast_let(
                    new_varname,
                    ast_mkclos(mk_clos_args),
                    ast_app_clos(app_clos_args)
                );
            }
        //case -> func_name is not a label -> convert to apply closure
        } else {
            plist app_clos_args =
                cons(t->params.tapp.t->params.v, empty());
            listNode *l_node = t->params.tapp.l->head;
            // messy loop, but using cons makes it reverse
            while(l_node != NULL){
                ptree tmp = (ptree)l_node->data;
                app_clos_args = append(
                    app_clos_args,
                    cons((char *)tmp->params.v, empty())
                );
                l_node = l_node->next;
            }
            return ast_app_clos(app_clos_args);
        }
    } else if (t->code == T_VAR){
        if (is_a_label(t->params.v)){
            // find fd in fd_list
            pfundef fd = get_fd(t->params.v);
            if (!fd){
                return t;
            }
            // case -> function with no free args
            if ((fd->free_vars == NULL) || (fd->free_vars->head == NULL)){
                return t;
            // case -> function with no free args
            } else {
                char *new_varname = gen_varname();
                plist mk_clos_args = append(
                    cons((void *)t->params.v, empty()),
                    fd->free_vars
                );
                return ast_let(
                    new_varname,
                    ast_mkclos(mk_clos_args),
                    ast_var(new_varname)
                );
            }
        } else {
            return t;
        }
    } else if (t->code == T_TUPLE){
        listNode *l_node = t->params.ttuple.l->head;
        while(l_node != NULL){
            ptree tmp = (ptree)l_node->data;
            if ((tmp->code == T_VAR) && (is_a_label(tmp->params.v))){
                char *new_varname = gen_varname();
                char *label_name = tmp->params.v;
                l_node->data = (void *)ast_var(new_varname);
                return ast_let(
                    new_varname,
                    apply_clos(ast_var(label_name)),
                    apply_clos(t)
                );
            }
            l_node = l_node->next;
        }
        return t;
    // case -> let var = label in whatever
    } else if ((t->code == T_LET) &&
                (t->params.tlet.t1->code == T_VAR) &&
                (is_a_label(t->params.tlet.t1->params.v))){
        return ast_let(
            t->params.tlet.v,
            ast_mkclos(cons(t->params.tlet.t1->params.v, empty())),
            apply_clos(t->params.tlet.t2)
        );
    // other cases -> call recursively
    } else {
        return apply_vis(t, apply_clos);
    }
}

ptree add_free_vars_refs(pfundef fd, listNode *current_var, int offset){
    if (current_var == NULL){
        return fd->body;
    } else {
        return ast_let(
            (char *)current_var->data,
            ast_get(ast_var("\%self"), ast_integ(offset)),
            add_free_vars_refs(fd, current_var->next, offset + 1)
        );
    }
}


ptree never_return_label(ptree t){
    assert(t);
    switch(t->code){
        case T_NEG :
        case T_NOT :
            if ((t->params.t->code == T_VAR) &&
                (is_a_label(t->params.t->params.v))){
                t->params.t = replace_label_by_var(t->params.t);
            } else  {
                return t;
            }

        case T_LET :
            if ((t->params.tlet.t2->code == T_VAR) &&
                (is_a_label(t->params.tlet.t2->params.v))){
                t->params.tlet.t2 = replace_label_by_var(t->params.tlet.t2);
            } else  {
                return t;
            }

        case T_LETTUPLE :
            if ((t->params.lettuple.t2->code == T_VAR) &&
                (is_a_label(t->params.lettuple.t2->params.v))){
                t->params.lettuple.t2 =
                    replace_label_by_var(t->params.lettuple.t2);
            } else  {
                return t;
            }

        case T_VAR :
            if (is_a_label(t->params.v)){
                t = replace_label_by_var(t);
            } else {
                return t;
            }
        // other cases -> all right, nothing to do
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_ADD :
        case T_SUB :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_IF :
        case T_LETREC :
        case T_APP :
        case T_TUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
        case T_MK_CLOS :
        case T_APP_CLOS :
            return t;
        default :
            fprintf(stderr, "TBI : in is_used_in_other_fd_bodies, code"
                " %d not yet implemented.\nExiting.\n", t->code);
            exit(1);
    }
}

ptree replace_label_by_var(ptree t){
    assert(t);
    assert(t->code == T_VAR);
    assert(is_a_label(t->params.v));
    pfundef fd = get_fd(t->params.v);
    if ((fd->free_vars == NULL) || (fd->free_vars->head == NULL)){
        char *new_var = gen_varname();
        return ast_let(
            new_var,
            ast_var(t->params.v),
            ast_var(new_var)
        );
    } else {
        return t;
    }
}
