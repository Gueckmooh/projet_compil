#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "list.h"
#include "env.h"
#include "closure.h"
#include "print_and_write.h"

extern plist fd_list;


/*
 * Detects and stores free variables for function definitions.
 * args contains the list of all variables which, under this scope, are
 * parameters of another function.
 * example :
 * let rec f x =
 *    let rec g y = x + y in g
 * in ....
 * during call of second let rec, args contains x cause x is a param of f, and
 * g is nested in f
 * but in
 * let rec f x = x + x in
 * let rec g y = y in ...
 * args is always, because there are no nested letrec declarations.
 */
 void detect_free_vars(ptree t, env_node *env){
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
            detect_free_vars(t->params.tletrec.fd->body, new_env);

            // call recursively on the continuation of function (after the in)
            // with the current env
            detect_free_vars(t->params.tletrec.t, env);

            // find function's free variables
            plist func_args = t->params.tletrec.fd->args;
            plist vars_in_body = get_list_of_vars_used(t->params.tletrec.fd->body);
            plist vars_created_in_body = get_list_of_vars_created(t->params.tletrec.fd->body);
            l_node = vars_in_body->head;
            t->params.tletrec.fd->free_vars = empty();
            t->params.tletrec.fd->glob_vars = empty();
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
                    t->params.tletrec.fd->glob_vars = cons(
                        (char *)l_node->data,
                        t->params.tletrec.fd->glob_vars
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
            detect_free_vars(t->params.t, env);
            return;
        // binary nodes
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            detect_free_vars(t->params.tbinary.t1, env);
            detect_free_vars(t->params.tbinary.t2, env);
            return;

        // ternary nodes
        case T_IF :
        case T_PUT :
            detect_free_vars(t->params.tternary.t1, env);
            detect_free_vars(t->params.tternary.t2, env);
            detect_free_vars(t->params.tternary.t3, env);
            return;

        // other cases
        case T_LET :
            detect_free_vars(t->params.tlet.t1, env);
            detect_free_vars(t->params.tlet.t2, env);
            return;

        case T_APP :
            detect_free_vars(t->params.tapp.t, env);
            return;

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                detect_free_vars((ptree)l_node->data, env);
                l_node = l_node->next;
            }
            return;

        case T_LETTUPLE :
            detect_free_vars(t->params.lettuple.t1, env);
            detect_free_vars(t->params.lettuple.t2, env);
            return;

        // TBI
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        default :
            fprintf(stderr, "TBI : detect_free_vars, code = %d\n"
            ". Exiting.\n", t->code);
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
                get_list_of_vars_used(t->params.tletrec.fd->body)
            );

        case T_LET :
            return append(
                get_list_of_vars_used(t->params.tlet.t1),
                get_list_of_vars_used(t->params.tlet.t2)
            );

        case T_APP :
            return append(
                t->params.tapp.l,
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
        default :
            fprintf(stderr, "TBI : detect_free_vars, code = %d.\n"
            "Exiting.\n", t->code);
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
            return append(
                t->params.tapp.l,
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
        default :
            fprintf(stderr, "TBI : detect_free_vars, code = %d.\n"
            "Exiting.\n", t->code);
            exit(1);
    }
}

bool has_only_bound_vars(char *func_label){
    listNode *l_node = fd_list->head;
    pfundef fd;
    while(l_node != NULL){
        fd = (pfundef)l_node->data;
        if(strcmp(fd->var, func_label) == 0){
            if((fd->glob_vars == NULL) && (fd->free_vars == NULL)){
                return true;
            } else {
                return false;
            }
        }
    }
    fprintf(stderr, "Error.In has_only_bound_vars, could not find label"
    " %s in fd_list.", func_label);
    exit(1);
}

void convert_fd_bodies(){
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        convert_fd_body((pfundef)l_node->data);
        l_node = l_node->next;
    }
}

void convert_fd_body(pfundef fd){

}

void print_fd_description(pfundef fd){
    printf("Function description :\n    name = %s\n    args = ", fd->var);
    print_str_list(fd->args);
    printf("\n    free vars = ");
    print_str_list(fd->free_vars);
    printf("\n    glob vars = ");
    print_str_list(fd->glob_vars);
    printf("\n    body = ");
    print_term(fd->body);
    printf("\n");
}

void print_all_fd_descriptions(){
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        print_fd_description((pfundef)l_node->data);
        l_node = l_node->next;
    }
}
