#include "ast.h"
#include "reduce_nested_let.h"

#include <assert.h>
#include <stdio.h>

ptree reduce_nested_let(ptree t){
    assert(t);
    switch(t->code){
        case T_INT :
            return ast_integ(t->params.i);

        case T_LET :
            t->params.tlet.t1 = reduce_nested_let(t->params.tlet.t1);
            t->params.tlet.t2 = reduce_nested_let(t->params.tlet.t2);
            if(t->params.tlet.t1->code == T_LET){
                return ast_let(
                    t->params.tlet.t1->params.tlet.v,
                    t->params.tlet.t1->params.tlet.t1,
                    ast_let(
                        t->params.tlet.v,
                        t->params.tlet.t2,
                        t->params.tlet.t1->params.tlet.t2
                    )
                );
            } else {
                return ast_let(
                        t->params.tlet.v,
                        t->params.tlet.t1,
                        t->params.tlet.t2
                );
            }
        case T_VAR :
            return ast_var(t->params.v);

        case T_ADD :
            return ast_add(
                reduce_nested_let(t->params.tbinary.t1),
                reduce_nested_let(t->params.tbinary.t2)
            );

        case T_SUB :
            return ast_add(
                reduce_nested_let(t->params.tbinary.t1),
                reduce_nested_let(t->params.tbinary.t2)
            );
        case T_UNIT :
            return ast_unit();
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
            printf("TBI. knorm, t->code = %d\n", t->code);
            return NULL;
    }
}
