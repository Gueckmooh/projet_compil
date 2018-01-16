#include "ast.h"
#include "utils.h"
#include "knorm.h"
#include "ast_to_asmlt.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

ptree knorm(ptree t){
    char *new_var1, *new_var2, *new_var3, *new_var4;
    listNode *l_node;
    ptree tmp;
    assert(t);
    switch(t->code){
        case T_LET :
            // case : let tup = (M1, ..., Mn) in N
            // if Mi is not a var, then we transform in
            // let v = Mi in let tup = (M1, ..., Mn) in N
            if (t->params.tlet.t1->code == T_TUPLE){
                l_node = t->params.tlet.t1->params.ttuple.l->head;
                while(l_node != NULL){
                    tmp = (ptree)(l_node->data);
                    if (tmp->code != T_VAR){
                        new_var1 = gen_varname();
                        l_node->data = (void *)ast_var(new_var1);
                        return knorm(
                            ast_let(
                                new_var1,
                                tmp,
                                t
                            )
                        );
                    }
                    l_node = l_node->next;
                }
            }
            // case : let x = M in (N1, ...,Nn)
            // replace with let x = M in let tup = (N1, ..., Nn) in tup
            if (t->params.tlet.t2->code == T_TUPLE){
                new_var1 = gen_varname();
                return ast_let(
                    t->params.tlet.v,
                    t->params.tlet.t1, // no need to knorm t1, it should be done already
                    knorm(
                        ast_let(
                            new_var1,
                            t->params.tlet.t2,
                            ast_var(new_var1)
                        )
                    )
                );
            }
            // normal case -> appply knorm recursively
            return ast_let(
                t->params.tlet.v,
                knorm(t->params.tlet.t1),
                knorm(t->params.tlet.t2)
            );

        case T_VAR :
            return t;

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
            if (t->params.tapp.t->code != T_VAR){
                new_var1 = gen_varname();
                tmp = t->params.tapp.t;
                t->params.tapp.t = ast_var(new_var1);
                return ast_let(
                    new_var1,
                    knorm(tmp),
                    k_norm_t_app(t, t->params.tapp.l->head)
                );
            } else {
                return k_norm_t_app(t, t->params.tapp.l->head);
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

        case T_TUPLE :
            return knorm_tuple(t, t->params.ttuple.l->head);
            // l_node = t->params.ttuple.l->head;
            // while(l_node != NULL){
            //     tmp = (ptree)l_node->data;
            //     if (tmp->code != T_VAR){
            //         new_var1 = gen_varname();
            //         l_node->data = (void *)ast_var(new_var1);
            //         return ast_let(
            //             new_var1,
            //             knorm(tmp),
            //             t
            //         );
            //     }
            //     l_node = l_node->next;
            // }
            // new_var1 = gen_varname();
            // return ast_let(
            //     new_var1,
            //     t,
            //     ast_var(new_var1)
            // );

        case T_LETTUPLE :
            // replace let (x1, ..., xn) = M in N
            // into    let y = M in
            //         let (x1, ..., xn) = y in N
            new_var1 = gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.lettuple.t1),
                ast_lettuple(
                    t->params.lettuple.l,
                    ast_var(new_var1),
                    knorm(t->params.lettuple.t2)
                )
            );

        case T_ARRAY :
            new_var1 = gen_varname();
            new_var2 = gen_varname();
#ifdef _ALLOCATE_BYTES_
            // dirty and ugly, we multiply per 4
            // so we change let x = array M N in
            // let v1 = knorm(M) in
            // let v3 = v1 + v1 in
            // let v4 = v3 + v3 in
            // let v2 = knorm(N) in
            // let x = array M N
            new_var3 = gen_varname();
            new_var4 = gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.tbinary.t1),
                ast_let(
                    new_var3,
                    ast_add(
                        ast_var(new_var1),
                        ast_var(new_var1)
                    ),
                    ast_let(
                        new_var4,
                        ast_add(
                            ast_var(new_var3),
                            ast_var(new_var3)
                        ),
                        ast_let(
                            new_var2,
                            knorm(t->params.tbinary.t2),
                            ast_app(
                                ast_var("create_array\0"),
                                cons(
                                    (void *)ast_var(new_var4),
                                    cons((void *)ast_var(new_var2), empty())
                                )
                            )
                        )
                    )
                )
            );
#else
            return ast_let(
                new_var1,
                knorm(t->params.tbinary.t1),
                ast_let(
                    new_var2,
                    knorm(t->params.tbinary.t2),
                    ast_app(
                        ast_var("create_array\0"),
                        cons(
                            (void *)ast_var(new_var1),
                            cons((void *)ast_var(new_var2), empty())
                        )
                    )
                )
            );
#endif
        case T_GET :
            new_var1 = gen_varname();
            new_var2 = gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.tbinary.t1),
                ast_let(
                    new_var2,
                    knorm(t->params.tbinary.t2),
                    ast_get(
                        ast_var(new_var1),
                        ast_var(new_var2)
                    )
                )
            );

        case T_PUT :
            new_var1 = gen_varname();
            new_var2 = gen_varname();
            new_var3 = gen_varname();
            return ast_let(
                new_var1,
                knorm(t->params.tternary.t1),
                ast_let(
                    new_var2,
                    knorm(t->params.tternary.t2),
                    ast_let(
                        new_var3,
                        knorm(t->params.tternary.t3),
                        ast_put(
                            ast_var(new_var1),
                            ast_var(new_var2),
                            ast_var(new_var3)
                        )
                    )
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
            return apply_vis(t, knorm);
        default :
            printf("Error : knorm, node code not recognized (%d)\n", t->code);
            return NULL;
    }
}

ptree k_norm_t_app(ptree t, listNode *arg_node){
    if (arg_node == NULL){
        return t;
    } else {
        char *new_varname = gen_varname();
        ptree tmp = (ptree)arg_node->data;
        arg_node->data = (void *)ast_var(new_varname);
        return ast_let(
            new_varname,
            knorm(tmp),
            k_norm_t_app(t, arg_node->next)
        );
    }
}

ptree knorm_tuple(ptree t, listNode *arg_node){
    if (arg_node == NULL){
        return t;
    } else {
        char *new_varname = gen_varname();
        ptree tmp = (ptree)arg_node->data;
        arg_node->data = (void *)ast_var(new_varname);
        return ast_let(
            new_varname,
            knorm(tmp),
            knorm_tuple(t, arg_node->next)
        );
    }
}
