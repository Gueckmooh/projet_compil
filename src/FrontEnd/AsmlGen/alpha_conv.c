#include "alpha_conv.h"
#include "ast.h"
#include "env.h"
#include "utils.h"
#include "stdio.h"
#include "list.h"

#include <assert.h>

ptree alpha_convert(ptree t, env_node *env){
    assert(t);
    char *new_varname, *new_funcname;
    env_node *new_env, *new_env_with_params;
    listNode *l_node;
    ptree t1, t2;
    switch(t->code){
        case T_VAR :
            t->params.v = epsilon(env, t->params.v);
            return t;

        case T_LET :
            new_varname = gen_varname();
            new_env = gen_env_node(t->params.tlet.v, new_varname, env);
            t1 = alpha_convert(t->params.tlet.t1, env);
            t2 = alpha_convert(t->params.tlet.t2,new_env);
            return ast_let(new_varname, t1, t2);

        case T_ADD :
            return ast_add(
                alpha_convert(t->params.tbinary.t1, env),
                alpha_convert(t->params.tbinary.t2, env)
            );

        case T_SUB :
            return ast_sub(
                alpha_convert(t->params.tbinary.t1, env),
                alpha_convert(t->params.tbinary.t2, env)
            );

        case T_APP :
            // replace args var_names if needed
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                l_node->data = (void *)alpha_convert(((ptree)l_node->data), env);
                l_node = l_node->next;
            }
            // case -> func_name is not in env -> prefix it with _min_caml_
            if(!is_in_env(env, t->params.tapp.t->params.v)){
                t->params.tapp.t->params.v =
                    prefix_funcname(t->params.tapp.t->params.v);

            // case -> func_name is in env -> apply epsilon to it
            } else {
                alpha_convert(t->params.tapp.t, env);
            }
            return t;

        case T_INT :
            return t;
        case T_NEG :
            t->params.t = alpha_convert(t->params.t, env);
            return t;
        case T_LETREC :
            new_funcname = gen_funcname();
            new_env = gen_env_node(t->params.tletrec.fd->var, new_funcname, env);
            l_node = t->params.tletrec.fd->args->head;
            new_env_with_params = new_env;
            while (l_node != NULL){
                new_varname = gen_varname();
                new_env_with_params = gen_env_node((char *) l_node->data,
                                                    new_varname,
                                                    new_env_with_params
                                                );
                l_node->data = (void *)new_varname;
                l_node = l_node->next;
            }
            alpha_convert(t->params.tletrec.fd->body, new_env_with_params);
            t->params.tletrec.fd->var = new_funcname;
            return ast_letrec(
                t->params.tletrec.fd,
                alpha_convert(t->params.tletrec.t, new_env)
            );
        case T_IF :
            return ast_if(
                alpha_convert(t->params.tternary.t1, env),
                alpha_convert(t->params.tternary.t2, env),
                alpha_convert(t->params.tternary.t3, env)
            );

        case T_EQ :
            return ast_eq(
                alpha_convert(t->params.tbinary.t1, env),
                alpha_convert(t->params.tbinary.t2, env)
            );

        case T_LE :
            return ast_le(
                alpha_convert(t->params.tbinary.t1, env),
                alpha_convert(t->params.tbinary.t2, env)
            );

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            while(l_node != NULL){
                l_node->data = (void *)alpha_convert((ptree)l_node->data, env);
                l_node = l_node->next;
            }
            return t;

        case T_LETTUPLE :
            l_node = t->params.lettuple.l->head;
            new_env = env;
            while(l_node != NULL){
                new_varname = gen_varname();
                new_env = gen_env_node((char *)l_node->data, new_varname, new_env);
                l_node->data = (char *)new_varname;
                l_node = l_node->next;
            }
            return ast_lettuple(
                t->params.lettuple.l,
                alpha_convert(t->params.lettuple.t1, env),
                alpha_convert(t->params.lettuple.t2, new_env)
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
        case T_ARRAY :
        case T_GET :
        case T_PUT :
        default :
            printf("TBI : alpha convert, code %d needs to be implem\n", t->code);
            return NULL;
    }

}
