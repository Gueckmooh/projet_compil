#include "ast.h"
#include "list.h"
#include "asml_parser_types.h"
#include "ast_to_asmlt.h"
#include "utils.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
asml_asmt_t *to_asml_asmt(ptree t){
    asml_asmt_t *new_asml_asmt = malloc(sizeof(asml_asmt_t));
    assert(t);
    switch(t->code){
        case T_LET :
            assert(t->params.tlet.t1->code != T_LET);
            new_asml_asmt->op = t->params.tlet.v;
            new_asml_asmt->exp = to_asml_exp(t->params.tlet.t1);
            new_asml_asmt->next = to_asml_asmt(t->params.tlet.t2);
            return new_asml_asmt;
        case T_ADD :
        case T_SUB :
        case T_APP :
        case T_UNIT :
        case T_INT :
        case T_NEG :
        case T_VAR :
            new_asml_asmt->op = NULL;
            new_asml_asmt->exp = to_asml_exp(t);
            new_asml_asmt->next = NULL;
            return new_asml_asmt;
        case T_BOOL :
            fprintf(
                stderr,
                "Error : trying to convert a T_BOOL ast -> should not happen\n");
            return NULL;
        case T_FLOAT :
        case T_NOT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_IF :
        case T_LETREC :
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

asml_exp_t *to_asml_exp(ptree t){
    asml_exp_t *new_exp = malloc(sizeof(asml_exp_t));
    assert(t);
    switch(t->code){
        case T_LET :
            printf("Error : convert let node in asml exp(nested let)\n");
            return NULL;
        case T_ADD :
        case T_SUB :
            new_exp->type = (t->code == T_ADD ? ASML_EXP_ADD : ASML_EXP_SUB);
            if (t->params.tbinary.t1->code == T_VAR){
                new_exp->op1 = (void *)t->params.tbinary.t1->params.v;
            } else {
                fprintf(
                    stderr,
                    "Error -> first operand of add exp is not a var.\n");
            }
            if (t->params.tbinary.t2->code == T_VAR){
                new_exp->op2 = (void *)t->params.tbinary.t2->params.v;
            } else if (t->params.tbinary.t2->code == T_INT){
                new_exp->op2 = (void *)int_to_str(t->params.tbinary.t2->params.i);
            } else {
                fprintf(
                    stderr,
                    "Error -> first operand of add exp is not a var.\n");
            }
            return new_exp;

        case T_INT :
            new_exp->type = ASML_EXP_INT;
            new_exp->op1 = int_to_str(t->params.i);
            return new_exp;

        case T_APP :
            new_exp->type = ASML_EXP_CALL;
            assert(t->params.tapp.t->code == T_VAR);
            new_exp->op1 = t->params.tapp.t->params.v;
            new_exp->op2 = args_list_to_asml_args_list(t->params.tapp.l);
            return new_exp;

        case T_BOOL :
            fprintf(
                stderr,
                "Error -> T_BOOL present in ast to asml_asmlt convert.\n");
                return NULL;

        case T_NEG :
                assert(t->params.t->code == T_VAR);
                new_exp->type = ASML_EXP_NEG;
                new_exp->op1 = t->params.t->params.v;
                return new_exp;

        case T_UNIT :
        case T_FLOAT :
        case T_NOT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        case T_EQ :
        case T_LE :
        case T_IF :
        case T_LETREC :
        case T_TUPLE :
        case T_LETTUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
        default :
            printf("TBI. ast_to_asml_asmt, t->code = %d\n", t->code);
            return NULL;
    }
}

asml_formal_arg_t *args_list_to_asml_args_list(plist ast_args_list){
    listNode *ast_node =ast_args_list->head;
    asml_formal_arg_t *current = NULL, *res = current;
    ptree ast_list_elem;
    while(ast_node != NULL){
        ast_list_elem = (ptree) ast_node->data;
        assert(ast_list_elem->code == T_VAR);
        current->next = malloc(sizeof(asml_formal_arg_t));
        current->next->val = ast_list_elem->params.v;
        current = current->next;
    }
    return res->next;
}
