#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "type.h"
#include "ast.h"
#include "assert.h"
#include "string.h"

#define MAX_ID 10

char buffer[MAX_ID];

id id_gen() {
    buffer[0] = '?';
    buffer[1] = 'v';
    static int cnt = 0;
    sprintf(buffer+2, "%d", cnt);
    char *res = malloc(sizeof(buffer));
    strcpy(res, buffer);
    cnt++;
    return res;
}

ptree ast_var(id v) {
    ptree t = malloc(sizeof(tree));
    t->code = T_VAR;
    t->params.v = v;
    return t;
}

ptree ast_unit() {
    ptree t = malloc(sizeof(tree));
    t->code = T_UNIT;
    return t;
}

ptree ast_let(id v, ptree t1, ptree t2) {
    ptree t = malloc(sizeof(tree));
    t->code = T_LET;
    t->params.tlet.v = v;
    t->params.tlet.t = gentvar();
    t->params.tlet.t1 = t1;
    t->params.tlet.t2 = t2;
    return t;
}

ptree ast_integ(int i) {
    ptree t = malloc(sizeof(tree));
    t->code = T_INT;
    t->params.i = i;
    return t;
}

ptree ast_float(float f) {
    ptree t = malloc(sizeof(tree));
    t->code = T_FLOAT;
    t->params.f = f;
    return t;
}

ptree ast_bool(bool b) {
    ptree t = malloc(sizeof(tree));
    t->code = T_BOOL;
    t->params.b = b;
    return t;
}

#define ptree_unary(CODE,t)  (\
        {ptree t2 = malloc(sizeof(tree));\
        t2->code = CODE;\
        t2->params.t = t;\
        return t2;})
// TODO; why bug if t instead of t2

#define ptree_binary(CODE,t1,t2)  (\
        {ptree t = malloc(sizeof(tree));\
        t->code = CODE;\
        t->params.tbinary.t1 = t1;\
        t->params.tbinary.t2 = t2;\
        return t;})

#define ptree_ternary(CODE,t1,t2,t3)  (\
        {ptree t = malloc(sizeof(tree));\
        t->code = CODE;\
        t->params.tternary.t1 = t1;\
        t->params.tternary.t2 = t2;\
        t->params.tternary.t3 = t3;\
        return t;})

ptree ast_not(ptree t) {
    ptree_unary(T_NOT, t);
}

ptree ast_neg(ptree t) {
    ptree_unary(T_NEG,t);
}

ptree ast_fneg(ptree t) {
    ptree_unary(T_FNEG,t);
}

ptree ast_add(ptree t1, ptree t2) {
    ptree_binary(T_ADD,t1,t2);
}

ptree ast_sub(ptree t1, ptree t2) {
    ptree_binary(T_SUB, t1, t2);
}

ptree ast_fadd(ptree t1, ptree t2) {
    ptree_binary(T_FADD, t1, t2);
}

ptree ast_fsub(ptree t1, ptree t2) {
    ptree_binary(T_FSUB, t1, t2);
}

ptree ast_fmul(ptree t1, ptree t2) {
    ptree_binary(T_FMUL, t1, t2);
}

ptree ast_fdiv(ptree t1, ptree t2) {
    ptree_binary(T_FDIV, t1, t2);
}

ptree ast_eq(ptree t1, ptree t2) {
    ptree_binary(T_EQ, t1, t2);
}

ptree ast_array(ptree t1, ptree t2) {
    ptree_binary(T_ARRAY, t1, t2);
}

ptree ast_get(ptree t1, ptree t2) {
    ptree_binary(T_GET, t1, t2);
}

ptree ast_le(ptree t1, ptree t2) {
    ptree_binary(T_LE, t1, t2);
}

ptree ast_if(ptree t1, ptree t2, ptree t3) {
    ptree_ternary(T_IF, t1, t2, t3);
}

ptree ast_put(ptree t1, ptree t2, ptree t3) {
    ptree_ternary(T_PUT, t1, t2, t3);
}

ptree ast_app(ptree t1, plist l) {
    ptree t = malloc(sizeof(tree));
    t->code = T_APP;
    t->params.tapp.t = t1;
    t->params.tapp.l = l;
    return t;
}

ptree ast_tuple(plist l) {
    ptree t = malloc(sizeof(tree));
    t->code = T_TUPLE;
    t->params.ttuple.l = l;
    return t;
}

ptree ast_lettuple(plist l, ptree t1, ptree t2) {
    ptree t = malloc(sizeof(tree));
    t->code = T_LETTUPLE;
    t->params.lettuple.l = l;
    t->params.lettuple.t1 = t1;
    t->params.lettuple.t2 = t2;
    return t;
}

ptree ast_letrec(pfundef fd, ptree t1) {
    ptree t = malloc(sizeof(tree));
    t->code = T_LETREC;
    t->params.tletrec.fd = fd;
    t->params.tletrec.t = t1;
    return t;
}


/**********************  DUPLICATING AST **************************************/

ptree build_unary(enum code code, ptree t){
    ptree new_t = malloc(sizeof(tree));
    new_t->code = code;
    new_t->params.t = t;
    return new_t;
}

ptree build_binary(enum code code, ptree t1, ptree t2){
    ptree new_t = malloc(sizeof(tree));
    new_t->code = code;
    new_t->params.tbinary.t1 = t1;
    new_t->params.tbinary.t2 = t2;
    return new_t;
}

ptree build_ternary(enum code code, ptree t1, ptree t2, ptree t3){
    ptree new_t = malloc(sizeof(tree));
    new_t->code = code;
    new_t->params.tternary.t1 = t1;
    new_t->params.tternary.t2 = t2;
    new_t->params.tternary.t3 = t3;
    return new_t;
}

ptree duplicate_ast(ptree t){
/* Duplicates a ptree (AST) structure
 * Args :
 *      t, pointer to the ptree to duplicate
 * Returns :
 *      the exact copy of t.
 */
    assert(t);
    switch (t->code) {

                        // simple expressions
        case T_UNIT :
            return ast_unit();
        case T_BOOL :
            return ast_bool(t->params.b);
        case T_INT :
            return ast_integ(t->params.i);
        case T_FLOAT :
            return ast_float(t->params.f);

                        // case : unary tree
        case T_NOT :
        case T_NEG :
        case T_FNEG :
            return build_unary(t->code, duplicate_ast(t->params.t));

                        // case : binary tree
        case T_ADD :
        case T_SUB :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_ARRAY :
        case T_GET :
            return build_binary(
                t->code,
                duplicate_ast(t->params.tbinary.t1),
                duplicate_ast(t->params.tbinary.t2)
            );

                        // case : ternary tree
        case T_IF :
        case T_PUT :
            return build_ternary(
                t->code,
                duplicate_ast(t->params.tternary.t1),
                duplicate_ast(t->params.tternary.t2),
                duplicate_ast(t->params.tternary.t3)
            );

                        // other cases
        case T_LET :
            return ast_let(
                copy_id(t->params.tlet.v),
                duplicate_ast(t->params.tlet.t1),
                duplicate_ast(t->params.tlet.t2)
            );
        case T_VAR :
            return ast_var(copy_id(t->params.v));
        case T_LETREC :
            return ast_letrec(
                copy_fundef(t->params.tletrec.fd),
                duplicate_ast(t->params.tletrec.t)
            );
        case T_APP :
            return ast_app(
                duplicate_ast(t->params.tapp.t),
                copy_list(t->params.tapp.l)
            );
        case T_TUPLE :
            return ast_tuple(copy_list(t->params.ttuple.l));
        case T_LETTUPLE :
            return ast_lettuple(
                copy_list(t->params.lettuple.l),
                duplicate_ast(t->params.lettuple.t1),
                duplicate_ast(t->params.lettuple.t2)
            );
        default:
             printf("%d ", t->code);
             assert(false);
    }
}

id copy_id(id original_id){
/* Duplicates a id (char *) content
 * Args :
 *      original_id, pointer to a char array
 * Returns :
 *      the exact copy of original_id.
 */
    assert(original_id);
    char * id_cpy = malloc(sizeof(MAX_ID));
    strcpy(id_cpy, original_id);
    return id_cpy;
}

pfundef copy_fundef(pfundef original_fd){
/* Duplicates a fundef struct content
 * Args :
 *      original_fd, pointer to a char array
 * Returns :
 *      the exact copy of original_fd, including a copy
 *      of the structures composing it.
 */
    assert(original_fd);
    pfundef fd_cpy = malloc(sizeof(struct fundef));
    fd_cpy->var = copy_id(original_fd->var);
    // TODO -> copy the type correctly
    memcpy((void *) &(fd_cpy->t), (void *) &(original_fd->t), sizeof(type));
    fd_cpy->args = copy_list(original_fd->args);
    fd_cpy->body = duplicate_ast(original_fd->body);
    return fd_cpy;
}
