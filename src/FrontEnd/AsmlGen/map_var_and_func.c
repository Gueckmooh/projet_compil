#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"
#include "list.h"
#include "map_var_and_func.h"

extern plist used_vars, created_vars, fd_list;
plist vars_to_remove;

bool removed_a_var;
/*
    Map all variables used in the program, then removes the unnecessary ones
*/
ptree eliminate_unnecessary_defs(ptree t){
    do {
        used_vars = get_list_of_vars_used(t);
        created_vars = get_list_of_vars_created(t);
        vars_to_remove = empty();
        listNode *l_node = created_vars->head;
        while(l_node != NULL){
            if(!is_in_str_list(used_vars, (char *)l_node->data)){
                vars_to_remove = cons(l_node->data, vars_to_remove);
            }
            l_node = l_node->next;
        }
        removed_a_var = false;
        t = remove_unused_vars(t);
    } while (removed_a_var);
    return t;
}

ptree remove_unused_vars(ptree t){
    assert(t);
    switch(t->code){
        // case let x = e1 in e2 -> if x is unused, replace with e2
        case T_LET :
            if (is_in_str_list(vars_to_remove, t->params.tlet.v)){
                printf("hop!\n");
                removed_a_var = true;
                return remove_unused_vars(t->params.tlet.t2);
            } else {
                return ast_let(
                    t->params.tlet.v,
                    remove_unused_vars(t->params.tlet.t1),
                    remove_unused_vars(t->params.tlet.t2)
                );
            }

        // leaves
        case T_VAR :
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
            return t;

        // unary nodes
        case T_NOT :
        case T_NEG :
            t->params.t = remove_unused_vars(t->params.t);
            return t;

        // binary nodes
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            t->params.tbinary.t1 = remove_unused_vars(t->params.tbinary.t1);
            t->params.tbinary.t2 = remove_unused_vars(t->params.tbinary.t2);
            return t;

        // ternary nodes
        case T_IF :
        case T_PUT :
            t->params.tternary.t1 = remove_unused_vars(t->params.tternary.t1);
            t->params.tternary.t2 = remove_unused_vars(t->params.tternary.t2);
            t->params.tternary.t3 = remove_unused_vars(t->params.tternary.t3);
            return t;

        // other cases
        case T_LETREC :
            t->params.tletrec.fd->body =
                remove_unused_vars(t->params.tletrec.fd->body);
            t->params.tletrec.t = remove_unused_vars(t->params.tletrec.t);
            return t;

        case T_APP :
            return t;

        case T_TUPLE :
            return t;

        case T_LETTUPLE :
            t->params.lettuple.t1 = remove_unused_vars(t->params.lettuple.t1);
            t->params.lettuple.t2 = remove_unused_vars(t->params.lettuple.t2);
            return t;

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            fprintf(stderr, "TBI : in remove_unused_vars, code = %d.\n"
            "Exiting.\n", t->code);
            exit(1);
        default :
            fprintf(stderr, "Error : in map_functions, incorrect node with "
            "code = %d.\nExiting.\n", t->code);
            exit(1);
    }
}


/*
 * returns the list of all variables used in t (ret a list of char *)
 */
plist get_list_of_vars_used(ptree t){
    plist l;
    listNode *l_node;
    assert(t);
    switch(t->code){
        case T_VAR :
            return cons(t->params.v, empty());

        // leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
            return empty();

        // unary nodes
        case T_NOT :
        case T_NEG :
            return get_list_of_vars_used(t->params.t);

        // binary nodes
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            return append(
                get_list_of_vars_used(t->params.tbinary.t1),
                get_list_of_vars_used(t->params.tbinary.t2)
            );

        // ternary nodes
        case T_IF :
        case T_PUT :
            return append(
                get_list_of_vars_used(t->params.tternary.t1),
                append(
                    get_list_of_vars_used(t->params.tternary.t2),
                    get_list_of_vars_used(t->params.tternary.t3)
                )
            );

        // other cases
        case T_LETREC :
            return append(
                get_list_of_vars_used(t->params.tletrec.t),
                cons(
                    t->params.tletrec.fd->var,
                    get_list_of_vars_used(t->params.tletrec.fd->body)
                )
            );

        case T_LET :
            if ((t->params.tlet.t1->code == T_APP) ||
                (t->params.tlet.t1->code == T_PUT)){
                l = cons(t->params.tlet.v, empty());
            } else {
                l = empty();
            }
            return append(
                l,
                append(
                    get_list_of_vars_used(t->params.tlet.t1),
                    get_list_of_vars_used(t->params.tlet.t2)
                )
            );

        case T_APP :
            l_node = t->params.tapp.l->head;
            l = empty();
            while(l_node != NULL){
                ptree tmp = (ptree)l_node->data;
                assert(tmp->code == T_VAR);
                l = cons((void *)(tmp->params.v), l);
                l_node = l_node->next;
            }
            return append(
                l,
                get_list_of_vars_used(t->params.tapp.t)
            );

        case T_TUPLE :
            l = empty();
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                l = append(l, get_list_of_vars_used((ptree)l_node->data));
                l_node = l_node->next;
            }
            return l;

        case T_LETTUPLE :
            return append(
                get_list_of_vars_used(t->params.lettuple.t1),
                get_list_of_vars_used(t->params.lettuple.t2)
            );

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            fprintf(stderr, "TBI : in map_functions, code = %d.\n"
            "Exiting.\n", t->code);
            exit(1);
        default :
            fprintf(stderr, "Error : in map_functions, incorrect node with "
            "code = %d.\nExiting.\n", t->code);
            exit(1);
    }
}


/*
 * returns the list of all variables used in t (ret a list of char *)
 */
 plist get_list_of_vars_created(ptree t){
    plist l;
    listNode *l_node;
    assert(t);
    switch(t->code){
        // leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_VAR :
            return empty();

        // unary nodes
        case T_NOT :
        case T_NEG :
            return get_list_of_vars_created(t->params.t);

        // binary nodes
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            return append(
                get_list_of_vars_created(t->params.tbinary.t1),
                get_list_of_vars_created(t->params.tbinary.t2)
            );

        // ternary nodes
        case T_IF :
        case T_PUT :
            return append(
                get_list_of_vars_created(t->params.tternary.t1),
                append(
                    get_list_of_vars_created(t->params.tternary.t2),
                    get_list_of_vars_created(t->params.tternary.t3)
                )
            );

        // other cases
        case T_LETREC :
            l = cons(t->params.tletrec.fd->var, empty());
            l_node = t->params.tletrec.fd->args->head;
            while (l_node != NULL){
                l = cons((char *)l_node->data, l);
                l_node = l_node->next;
            }
            return append(
                l,
                append(
                    get_list_of_vars_created(t->params.tletrec.t),
                    get_list_of_vars_created(t->params.tletrec.fd->body)
                )
            );

        case T_LET :
            return append(
                cons(t->params.tlet.v,empty()),
                append(
                    get_list_of_vars_created(t->params.tlet.t1),
                    get_list_of_vars_created(t->params.tlet.t2)
                )
            );

        case T_APP :
            l = empty();
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                ptree tmp = (ptree)l_node->data;
                l = cons(tmp->params.v, l);
                l_node = l_node->next;
            }
            return append(
                l,
                get_list_of_vars_created(t->params.tapp.t)
            );

        case T_TUPLE :
            l = empty();
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                l = append(l, get_list_of_vars_created((ptree)l_node->data));
                l_node = l_node->next;
            }
            return l;

        case T_LETTUPLE :
            l = empty();
            l_node = t->params.lettuple.l->head;
            while (l_node != NULL){
                l = cons((char *)l_node->data, l);
                l_node = l_node->next;
            }
            return append(
                l,
                append(
                    get_list_of_vars_created(t->params.lettuple.t1),
                    get_list_of_vars_created(t->params.lettuple.t2)
                )
            );

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            fprintf(stderr, "TBI : get_list_of_vars_created, code = %d.\n"
            "Exiting.\n", t->code);
            exit(1);
        default :
            fprintf(stderr, "Error : get_list_of_vars_created, code = %d"
            "(incorrect code).\nExiting.\n", t->code);
            exit(1);
    }
}



/*
 * Detects and stores free variables for function definitions.
 * args contains the list of all variables which, under this scope, are
 * parameters of another function.
 * example :
 * let rec f x =
 *    let rec g y = x + y in g
 * in ....
 * during call of second let rec, free_args contains x cause x is a param of f, and
 * g is nested in f
 * but in
 * let rec f x = x + x in
 * let rec g y = y in ...
 * free_args is always, because there are no nested letrec declarations.
 */
void map_functions(ptree t, env_node *env){
    env_node *new_env;
    listNode *l_node;
    assert(t);
    switch(t->code){
        case T_LETREC :
            // add the function descriptor to fd_list
            fd_list = cons(t->params.tletrec.fd, fd_list);

            // call recursively on body with enriched env, to detect free vars
            // in functions declared in this function
            new_env = env;
            l_node = t->params.tletrec.fd->args->head;
            while (l_node != NULL){
                new_env = gen_env_node((char *)l_node->data, NULL, new_env);
                l_node = l_node->next;
            }
            map_functions(t->params.tletrec.fd->body, new_env);

            // call recursively on the continuation of function (after the in)
            // with the current env
            map_functions(t->params.tletrec.t, env);

            // find function's free variables
            plist func_args = t->params.tletrec.fd->args;
            plist vars_in_body = get_list_of_vars_used(t->params.tletrec.fd->body);
            plist vars_created_in_body = get_list_of_vars_created(t->params.tletrec.fd->body);
            l_node = vars_in_body->head;
            t->params.tletrec.fd->free_vars = empty();
            while(l_node != NULL){
                // case -> variable is a parameter of 'above' function
                if(is_in_env(env, (char *)l_node->data)){
                    t->params.tletrec.fd->free_vars = cons(
                    (char *)l_node->data,
                    t->params.tletrec.fd->free_vars
                    );
                    // case -> variable was declared before function was declared
                } else if (
                    !is_in_str_list(func_args, (char *)l_node->data) &&
                    is_in_str_list(vars_in_body, (char *)l_node->data) &&
                    !is_in_str_list(vars_created_in_body, (char *)l_node->data)
                    ){
                    t->params.tletrec.fd->free_vars = cons(
                    (char *)l_node->data,
                    t->params.tletrec.fd->free_vars
                    );
                }
                l_node = l_node->next;
            }
            return;

        // leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_VAR :
            return;

        // unary nodes
        case T_NOT :
        case T_NEG :
            map_functions(t->params.t, env);
            return;

        // binary nodes
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            map_functions(t->params.tbinary.t1, env);
            map_functions(t->params.tbinary.t2, env);
            return;

        // ternary nodes
        case T_IF :
        case T_PUT :
            map_functions(t->params.tternary.t1, env);
            map_functions(t->params.tternary.t2, env);
            map_functions(t->params.tternary.t3, env);
            return;

        // other cases
        case T_LET :
            map_functions(t->params.tlet.t1, env);
            map_functions(t->params.tlet.t2, env);
            return;

        case T_APP :
            map_functions(t->params.tapp.t, env);
            return;

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                map_functions((ptree)l_node->data, env);
                l_node = l_node->next;
            }
            return;

        case T_LETTUPLE :
            map_functions(t->params.lettuple.t1, env);
            map_functions(t->params.lettuple.t2, env);
            return;

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            fprintf(stderr, "TBI : map_functions, code = %d not implem yet.\n"
            "Exiting.\n", t->code);
            exit(1);
        default :
            fprintf(stderr, "Error : map_functions, code ="
            " %d (incorrect).\nExiting.\n", t->code);
            exit(1);
    }
}

bool has_only_bound_vars(char *func_label){
    listNode *l_node = fd_list->head;
    pfundef fd;
    while(l_node != NULL){
        fd = (pfundef)l_node->data;
        if(strcmp(fd->var, func_label) == 0){
            if(fd->free_vars == NULL){
                return true;
            } else {
                return false;
            }
        }
        l_node = l_node->next;
    }
    fprintf(stderr, "Error.In has_only_bound_vars, could not find label"
    " %s in fd_list.", func_label);
    exit(1);
}
