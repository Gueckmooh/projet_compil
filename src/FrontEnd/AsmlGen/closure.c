#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "list.h"
#include "env.h"
#include "closure.h"
#include "print_and_write.h"
#include "utils.h"

extern plist fd_list;

ptree apply_closure_conversion(ptree t){
    // first apply closure conversion to function bodies
    listNode *l_node = fd_list->head;
    pfundef fd;
    while (l_node != NULL) {
        fd = (pfundef)l_node->data;
        fd->body = apply_clos(fd->body);
        if (fd->free_vars != NULL){
            fd->body = add_free_vars_refs(fd, fd->free_vars->head, 1);
        }
        l_node = l_node->next;
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
            if(!fd){
                return t;
            }
            // case -> function has no free vars -> leave it as is
            if (fd->free_vars->head == NULL){
                return t;
            // case -> function has free vars -> convert to make closure
            } else {
                char *new_varname = gen_varname();
                plist mk_clos_args = append(
                    cons(fd->var, empty()),
                    t->params.tapp.l
                );
                printf("ici\n");
                print_str_list(mk_clos_args);
                printf("\n");
                return ast_let(
                    new_varname,
                    ast_mkclos(mk_clos_args),
                    ast_var(new_varname)
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
            printf("\n");
            print_str_list(app_clos_args);
            printf("\n");
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
            if (fd->free_vars == NULL){
                return t;
            } else {
                char *new_varname = gen_varname();
                plist mk_clos_args = append(
                    cons((void *)t->params.v, empty()),
                    fd->free_vars
                );
                printf("la\n");
                print_str_list(mk_clos_args);
                printf("\n");
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
            add_free_vars_refs(fd, current_var->next, offset +1)
        );
    }
}
