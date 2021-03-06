#include "alpha_conv.h"
#include "ast.h"
#include "env.h"
#include "utils.h"
#include "list.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

ptree alpha_convert(ptree t, env_node *env){
    assert(t);
    char *new_varname, *new_funcname;
    env_node *new_env, *new_env_with_params;
    listNode *l_node;
    plist new_list;
    ptree t1, t2;
    switch(t->code){
        // Cases related to alpha conversion -> special treatment
        case T_VAR :
            return ast_var(epsilon(env, t->params.v));

        case T_LET :
            new_varname = gen_varname();
            new_env = gen_env_node(t->params.tlet.v, new_varname, env);
            t1 = alpha_convert(t->params.tlet.t1, env);
            t2 = alpha_convert(t->params.tlet.t2, new_env);
            return ast_let(new_varname, t1, t2);


        case T_APP :
            // replace args var_names if needed
            l_node = t->params.tapp.l->head;
            new_list = empty();
            while(l_node != NULL){
                new_list = append(
                    new_list,
                    cons((void *)alpha_convert(((ptree)l_node->data), env),
                         empty())
                );
                l_node = l_node->next;
            }
            // case -> func_name is not in env -> prefix it with _min_caml_
            if(!is_in_env(env, t->params.tapp.t->params.v)){
                t->params.tapp.t->params.v =
                    prefix_funcname(t->params.tapp.t->params.v);

            // case -> func_name is in env -> apply epsilon to it
            } else {
                t->params.tapp.t = alpha_convert(t->params.tapp.t, env);
            }
            return ast_app(
                alpha_convert(t->params.tapp.t, env),
                new_list
            );

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
            t->params.tletrec.fd->body =
                alpha_convert(t->params.tletrec.fd->body, new_env_with_params);
            t->params.tletrec.fd->var = new_funcname;
            return ast_letrec(
                t->params.tletrec.fd,
                alpha_convert(t->params.tletrec.t, new_env)
            );

        case T_TUPLE :
            l_node = t->params.ttuple.l->head;
            new_list = empty();
            while(l_node != NULL){
                new_list = append(
                    new_list,
                    cons(
                        (void *)alpha_convert((ptree)l_node->data, env),
                        empty()
                    )
                );
                l_node = l_node->next;
            }
            return ast_tuple(new_list);

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

        // leaves
        case T_INT :
        case T_UNIT :
        case T_BOOL :
        case T_FLOAT :
            return t;

        // unary nodes
        case T_NEG :
        case T_NOT :
        case T_FNEG :
            t->params.t = alpha_convert(t->params.t, env);
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
            t->params.tbinary.t1 = alpha_convert(t->params.tbinary.t1, env);
            t->params.tbinary.t2 = alpha_convert(t->params.tbinary.t2, env);
            return t;

        // ternary nodes
        case T_IF :
        case T_PUT :
            t->params.tternary.t1 = alpha_convert(t->params.tternary.t1, env);
            t->params.tternary.t2 = alpha_convert(t->params.tternary.t2, env);
            t->params.tternary.t3 = alpha_convert(t->params.tternary.t3, env);
            return t;

        case T_MK_CLOS:
        case T_APP_CLOS:
            fprintf(stderr, "TBI : alpha convert, code %d needs to be"
                " implemented.\nExiting.\n", t->code);
            exit(1);

        // Error -> an incorrect node has been submitted to the function
        default :
            fprintf(stderr, "Error : alpha convert, code %d unknown."
                "\nExiting.\n", t->code);
            exit(1);
    }

}

env_node *init_env(){
    return gen_env_node("print_int", "_min_caml_print_int", NULL);
}
