#include "alpha_conv.h"
#include "ast.h"
#include "env.h"
#include "utils.h"
#include "stdio.h"

#include <assert.h>

ptree alpha_convert(ptree t, plist env){
    assert(t);
    char *new_varname;
    plist new_env;
    ptree t1, t2;
    switch(t->code){
        case T_INT :
            return ast_integ(t->params.i);

        case T_VAR :
            return ast_var(epsilon(env, t->params.v));

        case T_LET :
            new_varname = alpha_gen_varname();
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

        case T_UNIT :
        case T_BOOL :

        case T_FLOAT :
        case T_NOT :
        case T_NEG :
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
        case T_LETTUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
        default :
            printf("TBI : alpha convert, %d needs to be implem\n", t->code);
            return NULL;
    }

}
