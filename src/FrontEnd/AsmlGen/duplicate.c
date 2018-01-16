#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ast.h"
#include "list.h"
#include "duplicate.h"

ptree duplicate_tree(ptree t){
    assert(t);
    switch(t->code){
        case T_UNIT :
            return ast_unit();
        case T_BOOL :
            return ast_bool(t->params.b);
        case T_INT :
            return ast_integ(t->params.i);
        case T_FLOAT :
            return ast_float(t->params.f);
        case T_NOT :
            return ast_not(duplicate_tree(t->params.t));
        case T_NEG :
            return ast_neg(duplicate_tree(t->params.t));
        case T_ADD :
            return ast_add(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_SUB :
            return ast_sub(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_FNEG :
            return ast_fneg(
                duplicate_tree(t->params.t)
            );
        case T_FADD :
            return ast_fadd(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_FSUB :
            return ast_fsub(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_FMUL :
            return ast_fmul(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_FDIV :
            return ast_fdiv(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_EQ :
            return ast_eq(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_LE :
            return ast_le(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_IF :
            return ast_if(
                duplicate_tree(t->params.tternary.t1),
                duplicate_tree(t->params.tternary.t2),
                duplicate_tree(t->params.tternary.t3)
            );
        case T_LET :
            return ast_let(
                duplicate_string(t->params.tlet.v),
                duplicate_tree(t->params.tlet.t1),
                duplicate_tree(t->params.tlet.t2)
            );
        case T_VAR :
            return ast_var(duplicate_string(t->params.v));
        case T_LETREC :
            return ast_letrec(
                duplicate_fundef(t->params.tletrec.fd),
                duplicate_tree(t->params.tletrec.t)
            );
        case T_APP :
            return ast_app(
                duplicate_tree(t->params.tapp.t),
                duplicate_ptree_list(t->params.tapp.l)
            );
        case T_TUPLE :
            return ast_tuple(
                duplicate_ptree_list(t->params.ttuple.l)
            );
        case T_LETTUPLE :
            return ast_lettuple(
                duplicate_str_list(t->params.lettuple.l),
                duplicate_tree(t->params.lettuple.t1),
                duplicate_tree(t->params.lettuple.t2)
            );
        case T_ARRAY :
            return ast_array(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_GET :
            return ast_get(
                duplicate_tree(t->params.tbinary.t1),
                duplicate_tree(t->params.tbinary.t2)
            );
        case T_PUT :
            return ast_put(
                duplicate_tree(t->params.tternary.t1),
                duplicate_tree(t->params.tternary.t2),
                duplicate_tree(t->params.tternary.t3)
            );
        case T_MK_CLOS :
            return ast_mkclos(
                duplicate_str_list(t->params.tclosure.l)
            );
        case T_APP_CLOS :
            return ast_app_clos(
                duplicate_str_list(t->params.tclosure.l)
            );
        default :
            fprintf(stderr, "Error in duplicate tree, code %d unknown.\n"
                "Exiting.\n", t->code);
            exit(1);
    }
}

char *duplicate_string(char *str){
    assert(str);
    char *res = malloc(sizeof(strlen(str) + 1));
    strcpy(res, str);
    return res;
}

plist duplicate_str_list(plist l){
    if (!l){
        return NULL;
    }
    plist res = empty();
    listNode *l_node = l->head;
    while(l_node != NULL){
        res = append(
            res,
            cons(
                duplicate_string((char *)l_node->data),
                empty()
            )
        );
        l_node = l_node->next;
    }
    return res;
}

plist duplicate_ptree_list(plist l){
    if (!l){
        return NULL;
    }
    plist res = empty();
    listNode *l_node = l->head;
    while(l_node != NULL){
        res = append(
            res,
            cons(
                duplicate_tree((ptree)l_node->data),
                empty()
            )
        );
        l_node = l_node->next;
    }
    return res;
}

pfundef duplicate_fundef(pfundef fd){
    pfundef res = malloc(sizeof(struct fundef));
    res->var = duplicate_string(fd->var);
    // TODO -> type
    res->args = duplicate_str_list(fd->args);
    res->free_vars = duplicate_str_list(fd->free_vars);
    res->body = duplicate_tree(fd->body);
    return res;
}
