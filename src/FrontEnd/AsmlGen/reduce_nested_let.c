#include "ast.h"
#include "reduce_nested_let.h"

#include <assert.h>
#include <stdio.h>

ptree reduce_nested_let(ptree t){
    assert(t);
    if (t->code == T_LET){
        t->params.tlet.t1 = reduce_nested_let(t->params.tlet.t1);
        t->params.tlet.t2 = reduce_nested_let(t->params.tlet.t2);
        if(t->params.tlet.t1->code == T_LET){
            return reduce_nested_let(ast_let(
                t->params.tlet.t1->params.tlet.v,
                t->params.tlet.t1->params.tlet.t1,
                ast_let(
                    t->params.tlet.v,
                    t->params.tlet.t1->params.tlet.t2,
                    t->params.tlet.t2
                )
            ));
        } else {
            return t;
        }
    } else {
        return apply_vis(t, reduce_nested_let);
    }
}
