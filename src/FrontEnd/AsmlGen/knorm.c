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
            // case -> several arithmetic operations in a row
            if ((t->params.tbinary.t1->code == T_ADD) ||
                (t->params.tbinary.t1->code == T_SUB) ||
                (t->params.tbinary.t2->code == T_ADD) ||
                (t->params.tbinary.t2->code == T_SUB)){
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
            // case -> 1st operand is not a variable
            } else if (t->params.tbinary.t1->code != T_VAR){
                new_var1 = knorm_gen_varname();
                return ast_let(
                    new_var1,
                    knorm(t->params.tbinary.t1),
                    ast_add(
                        ast_var(new_var1),
                        knorm(t->params.tbinary.t2)
                    )
                );
            // case -> 2nd operand is neither an int nor a variable
            } else if ((t->params.tbinary.t2->code != T_VAR) &&
                        t->params.tbinary.t2->code != T_INT){
                new_var1 = knorm_gen_varname();
                return ast_let(
                    new_var1,
                    knorm(t->params.tbinary.t2),
                    ast_add(
                        knorm(t->params.tbinary.t1),
                        ast_var(new_var1)
                    )
                );
            // case -> everything is fine
            } else {
                // return ast_add(t->params.tbinary.t1, t->params.tbinary.t2);
            }

        case T_SUB :
            // case -> several arithmetic operations in a row
            if ((t->params.tbinary.t1->code == T_ADD) ||
                (t->params.tbinary.t1->code == T_SUB) ||
                (t->params.tbinary.t2->code == T_ADD) ||
                (t->params.tbinary.t2->code == T_SUB)){
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
            // case -> 1st operand is not a variable
            } else if (t->params.tbinary.t1->code != T_VAR){
                new_var1 = knorm_gen_varname();
                return ast_let(
                    new_var1,
                    knorm(t->params.tbinary.t1),
                    ast_sub(
                        ast_var(new_var1),
                        knorm(t->params.tbinary.t2)
                    )
                );
            // case -> 2nd operand is neither an int nor a variable
            } else if ((t->params.tbinary.t2->code != T_VAR) &&
                        t->params.tbinary.t2->code != T_INT){
                new_var1 = knorm_gen_varname();
                return ast_let(
                    new_var1,
                    knorm(t->params.tbinary.t2),
                    ast_sub(
                        knorm(t->params.tbinary.t1),
                        ast_var(new_var1)
                    )
                );
            // case -> everything is fine
            } else {
                // return ast_sub(t->params.tbinary.t1, t->params.tbinary.t2);
            }
        case T_BOOL :
            // transforms a boolean in an int of {0,1}
            return ast_integ((t->params.b == true ? 1 : 0));

        case T_UNIT :
        case T_INT :
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
            apply_vis(t, knorm);
            break;
        default :
            printf("TBI. knorm, t->code = %d\n", t->code);
            return NULL;
    }
}
