#include "ast.h"
#include "utils.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ptree knorm(ptree t){
    char *new_var1, *new_var2;
    assert(t);
    switch(t->code){
        case T_INT :
            return ast_integ(t->params.i);

        case T_LET :
            new_var1 = cpy_str(t->params.tlet.v);;
            return ast_let(
                new_var1,
                knorm(t->params.tlet.t1),
                knorm(t->params.tlet.t2)
            );

        case T_VAR :
            new_var1 = cpy_str(t->params.v);
            return ast_var(new_var1);

        case T_ADD :
            new_var1 = knorm_gen_varname();
            new_var2 = knorm_gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.tbinary.t1),
                ast_let(
                    new_var2,
                    knorm(t->params.tbinary.t2),
                    ast_add(
                        ast_var(new_var1),
                        ast_var(new_var2)
                    )
                )
            );

        case T_SUB :
            new_var1 = knorm_gen_varname();
            new_var2 = knorm_gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.tbinary.t1),
                ast_let(
                    new_var2,
                    knorm(t->params.tbinary.t2),
                    ast_sub(
                        ast_var(new_var1),
                        ast_var(new_var2)
                    )
                )
            );

        case T_UNIT :
            return ast_unit();

        case T_BOOL :
            return ast_integ((t->params.b == true ? 1 : 0));

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
            printf("TBI. knorm, t->code = %d\n", t->code);
            return NULL;
    }
}
