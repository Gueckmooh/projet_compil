#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "env.h"


ptree beta_red(ptree t, env_node *env){
    assert(t);
    env_node *new_env;
    listNode *l_node;
    switch(t->code){
        case T_LET :
            if (t->params.tlet.t1->code == T_VAR){
                new_env = gen_env_node(t->params.tlet.v,
                                       t->params.tlet.t1->params.v,
                                       env
                                      );
                return beta_red(t->params.tlet.t2, new_env);
            } else {
                return ast_let(t->params.tlet.v,
                               beta_red(t->params.tlet.t1, env),
                               beta_red(t->params.tlet.t2, env)
                );
            }

        case T_VAR :
            return ast_var(epsilon(env, t->params.v));

        case T_ADD :
            return ast_add(
                beta_red(t->params.tbinary.t1, env),
                beta_red(t->params.tbinary.t1, env)
            );

        case T_SUB :
            return ast_sub(
                beta_red(t->params.tbinary.t1, env),
                beta_red(t->params.tbinary.t1, env)
            );

        case T_APP :
            // replace args var_names if needed
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                l_node->data = (void *)beta_red(((ptree)l_node->data), env);
                l_node = l_node->next;
            }
            return t;

        case T_INT :
            return t;

        case T_NEG:
            return ast_neg(beta_red(t->params.t, env));

        case T_LETREC:
            t->params.tletrec.fd->body = beta_red(t->params.tletrec.fd->body, env);
            return ast_letrec(
                t->params.tletrec.fd,
                beta_red(t->params.tletrec.t, env)
            );

        case T_IF:
            return ast_if(
                beta_red(t->params.tternary.t1, env),
                beta_red(t->params.tternary.t2, env),
                beta_red(t->params.tternary.t3, env)
            );

        case T_EQ :
            return ast_eq(
                    beta_red(t->params.tbinary.t1, env),
                    beta_red(t->params.tbinary.t2, env)
            );

        case T_LE :
            return ast_le(
                    beta_red(t->params.tbinary.t1, env),
                    beta_red(t->params.tbinary.t2, env)
            );

        case T_UNIT :
        case T_BOOL :
        case T_FLOAT :
        case T_NOT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_TUPLE :
        case T_LETTUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
        default :
            printf("TBI : beta_red, code %d needs to be implem\n", t->code);
            return NULL;
    }
}
