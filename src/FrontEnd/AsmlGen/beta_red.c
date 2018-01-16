#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "env.h"
#include "list.h"
#include "utils.h"

ptree beta_red(ptree t, env_node *env){
    assert(t);
    env_node *new_env;
    listNode *l_node;
    switch(t->code){
        // Cases related to beta reduction -> special treatment
        case T_LET :
            if ((t->params.tlet.t1->code == T_VAR) &&
                (!is_a_label(t->params.tlet.t1->params.v))){
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

        case T_APP :
        // replace args var_names if needed
            t->params.tapp.t = beta_red(t->params.tapp.t, env);
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                l_node->data = (void *)beta_red(((ptree)l_node->data), env);
                l_node = l_node->next;
            }
            return t;

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                l_node->data = (void *)beta_red(((ptree)l_node->data), env);
                l_node = l_node->next;
            }
            return t;

        // leaves
        case T_INT :
        case T_UNIT :
        case T_BOOL :
        case T_FLOAT :
            return t;

        // unary nodes
        case T_NEG:
        case T_NOT :
        case T_FNEG :
            t->params.t = beta_red(t->params.t, env);
            return t;

        // binary nodes
        case T_ADD :
        case T_SUB :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
            t->params.tbinary.t1 = beta_red(t->params.tbinary.t1, env);
            t->params.tbinary.t2 = beta_red(t->params.tbinary.t2, env);
            return t;

        // ternay nodes
        case T_IF:
        case T_PUT :
            t->params.tternary.t1 = beta_red(t->params.tternary.t1, env);
            t->params.tternary.t2 = beta_red(t->params.tternary.t2, env);
            t->params.tternary.t3 = beta_red(t->params.tternary.t3, env);
            return t;

        // other cases
        case T_LETREC:
            t->params.tletrec.fd->body = beta_red(t->params.tletrec.fd->body, env);
            return ast_letrec(
                t->params.tletrec.fd,
                beta_red(t->params.tletrec.t, env)
            );

        case T_LETTUPLE :
            return ast_lettuple(
                t->params.lettuple.l,
                beta_red(t->params.lettuple.t1, env),
                beta_red(t->params.lettuple.t2, env)
            );

        case T_MK_CLOS:
        case T_APP_CLOS:
            l_node = t->params.tclosure.l->head;
            char *var_name;
            while(l_node != NULL){
                var_name = (char *)l_node->data;
                l_node->data = epsilon(env, var_name);
                l_node = l_node->next;
            }
            return t;

        default :
            fprintf(stderr, "Error : beta_red called with incorrect"
                " tree node (code %d).\nExiting.\n", t->code);
            exit(1);
    }
}
