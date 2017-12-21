#include "alpha_conv.h"
#include "ast.h"
#include "env.h"
#include "utils.h"
#include "stdio.h"
#include "list.h"

#include <assert.h>

ptree alpha_convert(ptree t, plist env){
    assert(t);
    char *new_varname;
    plist new_env;
    listNode *l_node;
    ptree t1, t2;
    switch(t->code){
        case T_VAR :
            t->params.v = epsilon(env, t->params.v);
            return t;

        case T_LET :
            new_varname = gen_varname();
            new_env = cpy_env(env);
            add_or_replace(
                new_env,
                new_str_to_str(t->params.tlet.v,new_varname)
            );
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
            if(!is_in_env(t->params.tapp.t->params.v, env)){
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
        case T_UNIT :
        case T_BOOL :
        case T_FLOAT :
        case T_NOT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_IF :
        case T_LETREC :
        case T_TUPLE :
        case T_LETTUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
        default :
            printf("TBI : alpha convert, %d needs to be implem\n", t->code);
            return NULL;
    }

}
