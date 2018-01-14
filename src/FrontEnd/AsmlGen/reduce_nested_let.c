#include "ast.h"
#include "reduce_nested_let.h"
#include "print_and_write.h"

#include <assert.h>
#include <stdio.h>

ptree reduce_nested_let(ptree t){
    assert(t);
    if (t->code == T_LET){
        t->params.tlet.t1 = reduce_nested_let(t->params.tlet.t1);
        t->params.tlet.t2 = reduce_nested_let(t->params.tlet.t2);
        if((t->params.tlet.t1->code == T_LET)){
            return reduce_nested_let(ast_let(
                t->params.tlet.t1->params.tlet.v,
                t->params.tlet.t1->params.tlet.t1,
                ast_let(
                    t->params.tlet.v,
                    t->params.tlet.t1->params.tlet.t2,
                    t->params.tlet.t2
                )
            ));
        } else if (t->params.tlet.t1->code == T_LETTUPLE){
            return ast_lettuple(
                t->params.tlet.t1->params.lettuple.l,
                t->params.tlet.t1->params.lettuple.t1,
                ast_let(
                    t->params.tlet.v,
                    t->params.tlet.t1->params.lettuple.t2,
                    t->params.tlet.t2
                )
            );
        } else if (t->params.tlet.t1->code == T_LETREC){
            return ast_letrec(
                t->params.tlet.t1->params.tletrec.fd,
                ast_let(
                    t->params.tlet.v,
                    t->params.tlet.t1->params.tletrec.t,
                    t->params.tlet.t2
                )
            );
        } else {
            return t;
        }
    // } else if (t->code == T_LETREC){
    //     t->params.tletrec.fd->body =
    //         reduce_nested_let(t->params.tletrec.fd->body);
    //     t->params.tletrec.t = reduce_nested_let(t->params.tletrec.t);
    //     if(t->params.tletrec.fd->body->code == T_LET){
    //         return t;
    //         // ptree let_node = t->params.tletrec.fd->body;
    //         // t->params.tletrec.fd->body =
    //         //     t->params.tletrec.fd->body->params.tlet.t2;
    //         // return ast_let(
    //         //     let_node->params.tlet.v,
    //         //     let_node->params.tlet.t1,
    //         //     ast_letrec(
    //         //         t->params.tletrec.fd,
    //         //         t->params.tletrec.t
    //         //     )
    //         // );
    //     } else if(t->params.tletrec.fd->body->code == T_LETREC){
    //         // let rec f1 = (let rec f2 = M in N) in O becomes
    //         // let rec f2 = M in let rec f1 = N in O
    //         pfundef fd_f2 = t->params.tletrec.fd->body->params.tletrec.fd;
    //         t->params.tletrec.fd->body = t->params.tletrec.fd->body->params.tletrec.t; // N
    //         return ast_letrec(
    //             fd_f2,
    //             ast_letrec(
    //                 t->params.tletrec.fd,
    //                 t->params.tletrec.t
    //             )
    //         );
    //     } else if(t->params.tletrec.fd->body->code == T_LETTUPLE){
    //         return t;
    //         // return ast_lettuple(
    //         //     t->params.tletrec.fd->body->params.lettuple.l,
    //         //     t->params.tletrec.fd->body->params.lettuple.t1,
    //         //     ast_letrec(
    //         //         t->params.tletrec.fd,
    //         //         t->params.tletrec.fd->body->params.lettuple.t2
    //         //     )
    //         // );
    //     } else {
    //         return t;
    //     }
    } else if(t->code == T_LETTUPLE){
        t->params.lettuple.t1 = reduce_nested_let(t->params.lettuple.t1);
        t->params.lettuple.t2 = reduce_nested_let(t->params.lettuple.t2);
        if (t->params.lettuple.t1->code == T_LET){
            return ast_let(
                t->params.lettuple.t1->params.tlet.v,
                t->params.lettuple.t1->params.tlet.t1,
                ast_lettuple(
                    t->params.lettuple.l,
                    t->params.lettuple.t1->params.tlet.t2,
                    t->params.lettuple.t2
                )
            );
        } else if (t->params.lettuple.t1->code == T_LETREC){
            return ast_letrec(
                t->params.lettuple.t1->params.tletrec.fd,
                ast_lettuple(
                    t->params.lettuple.l,
                    t->params.lettuple.t1->params.tletrec.t,
                    t->params.lettuple.t2
                )
            );
        } else if (t->params.lettuple.t1->code == T_LETTUPLE){
            return ast_lettuple(
                t->params.lettuple.t1->params.lettuple.l,
                t->params.lettuple.t1->params.lettuple.t1,
                ast_lettuple(
                    t->params.lettuple.l,
                    t->params.lettuple.t1->params.lettuple.t2,
                    t->params.lettuple.t2
                )
            );
        } else {
            return t;
        }
    } else {
        return apply_vis(t, reduce_nested_let);
    }
}
