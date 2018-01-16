#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"
#include "list.h"
#include "env.h"
#include "constant_folding.h"

bool folded_a_const;

ptree apply_constant_folding(ptree t){
    do {
        folded_a_const = false;
        t = constant_folding(t, NULL);
    } while (folded_a_const);
    return t;
}

ptree constant_folding(ptree t, env_node *env){
    assert(t);
    switch(t->code){
        //leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
            return t;

        case T_VAR :
            return replace_var(t, env);

        case T_TUPLE :
            // l_node = t->params.ttuple.l->head;
            // while (l_node != NULL){
            //     if(((ptree)l_node->data)->code == T_VAR){
            //         l_node->data = (void *)replace_var((ptree)l_node->data, env);
            //     }
            //     l_node = l_node->next;
            // }
            return t;

        // unary
        case T_NOT :
            fprintf(stderr, "Error, trying to convert a T_NOT node in"
            " constant folding.\nThis should never happen");
            exit(1);

        case T_NEG :
            if (t->params.t->code == T_NEG){
                return constant_folding(t->params.t->params.t, env);
            }
            return ast_neg(constant_folding(t->params.t, env));

        // binary
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
            t->params.tbinary.t1 = constant_folding(t->params.tbinary.t1, env);
            t->params.tbinary.t2 = constant_folding(t->params.tbinary.t2, env);
            if (
                ( (t->params.tbinary.t1->code == T_INT) ||
                  (
                    (t->params.tbinary.t1->code == T_NEG) &&
                    (t->params.tbinary.t1->params.t->code == T_INT)
                  )
                )
            &&
                ( (t->params.tbinary.t2->code == T_INT) ||
                  (
                    (t->params.tbinary.t2->code == T_NEG) &&
                    (t->params.tbinary.t2->params.t->code == T_INT)
                  )
                )
            ){
                int v1 = (t->params.tbinary.t1->code == T_INT ?
                            t->params.tbinary.t1->params.i :
                            (-1) * (t->params.tbinary.t1->params.t->params.i)
                );
                int v2 = (t->params.tbinary.t2->code == T_INT ?
                            t->params.tbinary.t2->params.i :
                            (-1) * (t->params.tbinary.t2->params.t->params.i)
                );
                switch (t->code){
                    case T_ADD:
                        return (
                            v1 + v2 >= 0 ?
                            ast_integ(v1+v2) :
                            ast_neg(ast_integ(-v1-v2))
                        );

                    case T_SUB :
                        return (
                            v1 - v2 >= 0 ?
                            ast_integ(v1 - v2) :
                            ast_neg(ast_integ(v2 - v1))
                        );

                    case T_EQ :
                        return (
                            v1 == v2 ?
                            ast_integ(1) : ast_integ(0)
                        );

                    case T_LE :
                    return (
                        v1 <= v2 ?
                        ast_integ(1) : ast_integ(0)
                    );

                    default :
                        return NULL; // dummy gcc
                }
            } else {
                return t;
            }

        case T_ARRAY :
            t->params.tbinary.t1 = constant_folding(t->params.tbinary.t1, env);
            t->params.tbinary.t2 = constant_folding(t->params.tbinary.t2, env);
            return t;

        case T_GET :
            t->params.tbinary.t2 = constant_folding(t->params.tbinary.t2, env);
            return t;

        // ternary
        case T_IF :
            t->params.tternary.t1 = constant_folding(t->params.tternary.t1, env);
            t->params.tternary.t2 = constant_folding(t->params.tternary.t2, env);
            t->params.tternary.t3 = constant_folding(t->params.tternary.t3, env);
            if (t->params.tternary.t1->code == T_INT){
                if (t->params.tternary.t1->params.i == 0){
                    return t->params.tternary.t2;
                } else {
                    return t->params.tternary.t3;
                }
            } else if ((t->params.tternary.t1->code == T_NEG) &&
                       (t->params.tternary.t1->params.t->code == T_INT)){
               if (t->params.tternary.t1->params.i == 0){
                   return t->params.tternary.t2;
               } else {
                   return t->params.tternary.t3;
               }
           } else {
               return t;
           }

        case T_PUT :
            t->params.tternary.t2 = constant_folding(t->params.tternary.t2, env);
            t->params.tternary.t3 = constant_folding(t->params.tternary.t3, env);
            return t;

        // other cases
        case T_LET :
            if (t->params.tlet.t1->code == T_INT){
                env = gen_env_node_int(
                    t->params.tlet.v,
                    t->params.tlet.t1->params.i,
                    env
                );
                if (can_fold(t->params.tlet.v, t)){
                    folded_a_const = true;
                    return (constant_folding(t->params.tlet.t2, env));
                }
                t->params.tlet.t2 = constant_folding(t->params.tlet.t2, env);
            } else if ((t->params.tlet.t1->code == T_NEG) &&
                       (t->params.tlet.t1->params.t->code == T_INT)){
               env = gen_env_node_int(
                   t->params.tlet.v,
                   ((-1) * (t->params.tlet.t1->params.t->params.i)),
                   env
               );
               t->params.tlet.t2 = constant_folding(t->params.tlet.t2, env);
           } else {
               t->params.tlet.t1 = constant_folding(t->params.tlet.t1, env);
               t->params.tlet.t2 = constant_folding(t->params.tlet.t2, env);
           }
           return t;

        case T_LETREC :
            t->params.tletrec.fd->body =
                constant_folding(t->params.tletrec.fd->body, env);
            t->params.tletrec.t = constant_folding(t->params.tletrec.t, env);
            return t;

        case T_LETTUPLE :
            t->params.lettuple.t1 = constant_folding(t->params.lettuple.t1, env);
            t->params.lettuple.t2 = constant_folding(t->params.lettuple.t2, env);
            return t;

        case T_APP :
            return t;

        case T_MK_CLOS :
        case T_APP_CLOS :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        default :
            fprintf(stderr, "TBI : in constant_folding, code %d not yet implemented.\n"
            "Exiting.\n", t->code);
            exit(1);
    }
}



/*
 * Checks if the variable is used as an argument for a function call in the tree
 * if no -> can fold, return true
 * else return false cause cannot fold
 */
bool can_fold(char *var_name, ptree t){
    assert(t);
    listNode *l_node;
    switch(t->code){
        // function  call -> check if var_name is one of the arguments
        case T_APP :
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                assert(((ptree)l_node->data)->code == T_VAR);
                if(strcmp(var_name, ((ptree)l_node->data)->params.v) == 0){
                    return false;
                }
                l_node = l_node->next;
            }
            return true;

        //leaves
        case T_UNIT :
        case T_BOOL :
        case T_INT :
        case T_FLOAT :
        case T_VAR :
            return true;

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                assert(((ptree)l_node->data)->code == T_VAR);
                if(strcmp(var_name, ((ptree)l_node->data)->params.v) == 0){
                    return false;
                }
                l_node = l_node->next;
            }
            return true;

        // unary
        case T_NOT :
        case T_NEG :
            return can_fold(var_name, t->params.t);

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
                can_fold(var_name, t->params.tbinary.t1) &&
                can_fold(var_name, t->params.tbinary.t2)
            );

        // ternary
        case T_IF :
        case T_PUT :
            return (
                can_fold(var_name, t->params.tternary.t1) &&
                can_fold(var_name, t->params.tternary.t2) &&
                can_fold(var_name, t->params.tternary.t3)
            );

        // other cases
        case T_LET :
            return (
                can_fold(var_name, t->params.tlet.t1) &&
                can_fold(var_name, t->params.tlet.t2)
            );

        case T_LETREC :
            return (
                can_fold(var_name, t->params.tletrec.fd->body) &&
                can_fold(var_name, t->params.tletrec.t)
            );

        case T_LETTUPLE :
            return (
                can_fold(var_name, t->params.lettuple.t1) &&
                can_fold(var_name, t->params.lettuple.t2)
            );

        case T_MK_CLOS :
        case T_APP_CLOS :
        default :
            fprintf(stderr, "TBI : in can_fold, code %d not yet implemented.\n"
            "Exiting.\n", t->code);
            exit(1);
    }
}

ptree replace_var(ptree t, env_node *env){
    if(is_in_env(env, t->params.v)){
        folded_a_const = true;
        int value = get_value(t->params.v, env);
        if (value >= 0){
            return ast_integ(value);
        } else {
            return ast_neg(ast_integ((-1) * value));
        }
    } else {
        return t;
    }
}
