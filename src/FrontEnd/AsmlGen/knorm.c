#include "ast.h"
#include "utils.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ptree knorm(ptree t){
    char *new_var1, *new_var2;
    listNode *l_node;
    ptree tmp;
    assert(t);
    switch(t->code){
        case T_LET :
            new_var1 = cpy_str(t->params.tlet.v);
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
                new_var1 = gen_varname();
                new_var2 = gen_varname();
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
                new_var1 = gen_varname();
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
                new_var1 = gen_varname();
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
                return t;
            }

        case T_SUB :
            // case -> several arithmetic operations in a row
            if ((t->params.tbinary.t1->code == T_ADD) ||
                (t->params.tbinary.t1->code == T_SUB) ||
                (t->params.tbinary.t2->code == T_ADD) ||
                (t->params.tbinary.t2->code == T_SUB)){
                new_var1 = gen_varname();
                new_var2 = gen_varname();
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
                new_var1 = gen_varname();
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
                new_var1 = gen_varname();
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
                return t;
            }

        case T_BOOL :
            // transforms a boolean in an int of {0,1}
            return ast_integ((t->params.b == true ? 1 : 0));

        case T_APP :
            // case -> func name is not a var -> insert let
            if (t->params.tapp.t->code != T_VAR){
                new_var1 = gen_funcname();
                tmp = t->params.tapp.t;
                t->params.tapp.t = ast_var(new_var1);
                return knorm(ast_let(new_var1, tmp, t));
            }

            // case -> one of args is not a var but an expression -> insert let
            l_node = t->params.tapp.l->head;
            while(l_node != NULL){
                if (((ptree)l_node->data)->code != T_VAR){
                    new_var1 = gen_varname();
                    tmp = (ptree)(l_node->data);
                    l_node->data = (void *)ast_var(new_var1);
                    return knorm(ast_let(new_var1, tmp, t));
                }
                l_node = l_node->next;
            }

        case T_NEG :
            if(t->params.t->code != T_VAR){
                new_var1 = gen_varname();
                return ast_let(
                    new_var1,
                    knorm(t->params.t),
                    ast_neg(ast_var(new_var1))
                );
            } else {
                return t;
            }

        case T_NOT :
            return knorm(ast_sub(ast_integ(1), t->params.t));

        case T_IF :
            // case -> trivial (if true or if false)
            if (t->params.tternary.t1->code == T_BOOL){
                if (t->params.tternary.t1->params.b){
                    return knorm(t->params.tternary.t2);
                } else {
                    return knorm(t->params.tternary.t3);
                }
            }
            // case -> the condition is a comparison A op B
            if ((t->params.tternary.t1->code == T_EQ) ||
                (t->params.tternary.t1->code == T_LE)){
                new_var1 = gen_varname();
                new_var2 = gen_varname();
                return ast_let(
                    new_var1,
                    knorm(t->params.tternary.t1->params.tbinary.t1),
                    ast_let(
                        new_var2,
                        knorm(t->params.tternary.t1->params.tbinary.t2),
                        ast_if(
                            (t->params.tternary.t1->code == T_EQ ?
                             ast_eq(ast_var(new_var1), ast_var(new_var2)) :
                             ast_le(ast_var(new_var1), ast_var(new_var2))
                            ),
                            knorm(t->params.tternary.t2),
                            knorm(t->params.tternary.t3)
                        )
                    )
                );
            }
            // case -> the condition is neither a bool, nor a comparison
            new_var1 = gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.tternary.t1),
                ast_if(
                    ast_eq(ast_var(new_var1), ast_integ(0)),
                    knorm(t->params.tternary.t3),
                    knorm(t->params.tternary.t2)
                )
            );

        case T_UNIT :
        case T_INT :
        case T_FLOAT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_LETREC :
        case T_TUPLE :
        case T_LETTUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
            return apply_vis(t, knorm);
        default :
            printf("Error : knorm, node code not recognized (%d)\n", t->code);
            return NULL;
    }
}
