#include "ast.h"
#include "list.h"
#include "asml_parser_types.h"
#include "ast_to_asmlt.h"
#include "utils.h"
#include "asml_parser_driver.h"
#include "print_and_write.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern plist fd_list;
pfundef current_fd;


asml_function_t *build_asml_from_ptree(ptree t){
    // first we send all fd to the asml parser
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        current_fd = (pfundef)l_node->data;
        send_func_d_to_asml_parser(current_fd);
        l_node = l_node->next;
    }
    current_fd = NULL;
    asml_function_t *result = malloc(sizeof(asml_function_t));
    result->name = malloc(6);
    strcpy(result->name, "main");
    result->args = NULL;
    result->asmt = to_asml_asmt(t);
    // print_asml_fun(result);
    return result;
}

asml_asmt_t *to_asml_asmt(ptree t){
    asml_asmt_t *new_asml_asmt = malloc(sizeof(asml_asmt_t));
    assert(t);
    switch(t->code){
        case T_LET :
            assert(t->params.tlet.t1->code != T_LET);
            // case : let tup = (M1, ...,, Mn) in N -> special care :)
            if (t->params.tlet.t1->code == T_TUPLE){
                return tuple_to_asml_asmt(t);
            } else if (t->params.tlet.t1->code == T_ARRAY){
                fprintf(stderr, "Error : Trying to convert a T_ARRAY in to_asml_asmt.\n"
                    "This should never happen\n");
                exit(1);
            } else if (t->params.tlet.t1->code == T_MK_CLOS){
                return mk_clos_to_asml_asmt(t);
            } else {
                // non tuple case
                new_asml_asmt->op = t->params.tlet.v;
                new_asml_asmt->exp = to_asml_exp(t->params.tlet.t1);
                new_asml_asmt->next = to_asml_asmt(t->params.tlet.t2);
                return new_asml_asmt;
            }
        case T_ADD :
        case T_SUB :
        case T_APP :
        case T_UNIT :
        case T_INT :
        case T_NEG :
        case T_VAR :
        case T_IF :
        case T_EQ :
        case T_LE :
        case T_MK_CLOS :
        case T_APP_CLOS :
            new_asml_asmt->op = NULL;
            new_asml_asmt->exp = to_asml_exp(t);
            new_asml_asmt->next = NULL;
            return new_asml_asmt;

        case T_BOOL :
        case T_NOT :
            fprintf(
                stderr,
                "Error : trying to convert a T_BOOL or a T_NOT ast -> should "
                "not happen(code %d)\n", t->code);
            return NULL;

        case T_LETREC :
            fprintf(stderr, "Error, trying to convert a T_LETREC node "
                "in to_asml_asmt.\nExiting.\n");
            exit(1);

        case T_LETTUPLE :
            assert(t->params.lettuple.t1->code == T_VAR);
            return lettuple_to_asmlt(t);

        case T_TUPLE :
        case T_ARRAY :
        case T_GET :
        case T_PUT :
            fprintf(stderr, "Error, trying to convert ast node with code %d in ast "
            "in to_asml_asmt.\nThis should not happen.\n", t->code);
            exit(1);

            fprintf(stderr, "Encountered T_MK_CLOS or T_APP_CLOS in ast_to_asmlt.\nSo "
                "just implement it.\n");
            exit(1);

        case T_FLOAT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        default :
            printf("TBI. ast to asmlt, t->code = %d\n", t->code);
            exit(1);
    }
}

asml_exp_t *to_asml_exp(ptree t){
    asml_exp_t *new_exp = malloc(sizeof(asml_exp_t));
    assert(t);
    switch(t->code){
        case T_LET :
            printf("Error : trying to convert let node in asml exp(nested let)"
            "in to_asml_exp\n");
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

        case T_APP_CLOS :
            new_exp->type = ASML_EXP_CLOSURE;
            assert(t->params.tclosure.l->head);
            plist args_list = t->params.tclosure.l;
            listNode *l_node = args_list->head;
            new_exp->op1 = (char *)l_node->data;
            args_list->head = l_node->next;
            args_list->logicalLength --;
            new_exp->op2 = string_list_to_asml_args_list(args_list);
            return new_exp;

        case T_BOOL :
            fprintf(
                stderr,
                "Error -> T_BOOL present in ast to asml_asmlt convert.\
                This should not happen.\n"
            );
            return NULL;

        case T_NEG :
            assert(t->params.t->code == T_VAR);
            new_exp->type = ASML_EXP_NEG;
            new_exp->op1 = t->params.t->params.v;
            return new_exp;

        case T_IF :
            new_exp->type = ASML_EXP_IF;
            new_exp->op1 = to_asml_exp(t->params.tternary.t1);
            new_exp->op2 = (asml_asmt_t *)to_asml_asmt(t->params.tternary.t2);
            new_exp->op3 = (asml_asmt_t *)to_asml_asmt(t->params.tternary.t3);
            return new_exp;

        case T_EQ :
        case T_LE :
            assert((t->params.tbinary.t1->code == T_VAR) &&
                   ((t->params.tbinary.t2->code == T_VAR) ||
                    (t->params.tbinary.t2->code == T_INT))
                  );
            new_exp->type = (t->code == T_EQ ? ASML_COND_EQUAL : ASML_COND_LE);
            new_exp->op1 = t->params.tbinary.t1->params.v;
            new_exp->op2 = (t->params.tbinary.t2->code == T_VAR ?
                            t->params.tbinary.t1->params.v :
                            int_to_str(t->params.tbinary.t1->params.i)
                           );
            return new_exp;

        case T_VAR :
            new_exp->type = ASML_EXP_IDENT;
            new_exp->op1 = t->params.v;
            return new_exp;

        case T_TUPLE :
            printf("Error : trying to convert a T_TUPLE ast in asml_exp\n"
            "this souhld never happen\n");
            return NULL;

        case T_ARRAY :
            printf("Error : trying to convert a T_ARRAY in to_asml_exp.\n"
            "This should never happen\n");
            exit(1);

        case T_GET :
            assert(t->params.tbinary.t1->code == T_VAR);
            assert((t->params.tbinary.t2->code == T_VAR) ||
                    (t->params.tbinary.t2->code == T_INT));
            new_exp->type = ASML_MEM_READ;
            new_exp->op1 = t->params.tbinary.t1->params.v;
            new_exp->op2 = (
                t->params.tbinary.t2->code == T_VAR ?
                t->params.tbinary.t2->params.v :
                int_to_str(WORD_SIZE * t->params.tbinary.t2->params.i)
            );
            new_exp->op3 = NULL;
            return new_exp;

        case T_PUT :
            assert(t->params.tternary.t1->code == T_VAR);
            assert((t->params.tternary.t2->code == T_VAR) ||
                   (t->params.tternary.t2->code == T_INT));
            assert(t->params.tternary.t3->code == T_VAR);
            new_exp->type = ASML_MEM_WRITE;
            new_exp->op1 = t->params.tternary.t1->params.v;
            new_exp->op2 = (
                t->params.tternary.t2->code == T_VAR ?
                t->params.tternary.t2->params.v :
                int_to_str(WORD_SIZE * t->params.tternary.t2->params.i)
            );
            new_exp->op3 = (
                t->params.tternary.t3->code == T_VAR ?
                t->params.tternary.t3->params.v :
                int_to_str(WORD_SIZE * t->params.tternary.t3->params.i)
            );;
            return new_exp;

        case T_LETREC :
        case T_LETTUPLE :
        case T_NOT :
            fprintf(stderr, "Error : in ast_to_asml_exp, tryong to convert a "
            "node with code %d.\nThis should never happen.Exiting\n", t->code);
            exit(1);

        case T_UNIT :
            fprintf(stderr, "Encountered unit node in ast_to_asml_exp.\n"
                "Exiting.\n");
            exit(1);

        case T_MK_CLOS :
            fprintf(stderr, "Error, trying to convert a T_MK_CLOS node in "
                    "to_asml_exp.This should never happen.\nExiting.\n");
            exit(1);
        case T_FLOAT :
        case T_FNEG :
        case T_FADD :
        case T_FSUB :
        case T_FMUL :
        case T_FDIV :
        default :
            fprintf(stderr, "TBI. ast_to_asml_exp, t->code = %d\n", t->code);
            exit(1);
    }
}

// copies a list of ptrees
asml_formal_arg_t *args_list_to_asml_args_list(plist ast_args_list){
    if(ast_args_list == NULL){
        return NULL;
    }
    listNode *ast_node = ast_args_list->head;
    ptree ast_list_elem = (ptree) ast_node->data;
    ast_node = ast_node->next;
    asml_formal_arg_t *result = malloc(sizeof(asml_formal_arg_t)), *current = result;
    assert(ast_list_elem->code == T_VAR);
    result->val = ast_list_elem->params.v;
    while(ast_node != NULL){
        current->next = malloc(sizeof(asml_formal_arg_t));
        current = current->next;
        ast_list_elem = (ptree) ast_node->data;
        current->val = ast_list_elem->params.v;
        ast_node = ast_node->next;
    }
    current->next = NULL;
    return result;
}

// copies a list of char*
asml_formal_arg_t *string_list_to_asml_args_list(plist str_list){
    if(str_list == NULL){
        return NULL;
    }
    listNode *ast_node = str_list->head;
    char *ast_list_elem = (char *) ast_node->data;
    ast_node = ast_node->next;
    asml_formal_arg_t *result = malloc(sizeof(asml_formal_arg_t)), *current = result;
    result->val = ast_list_elem;
    while(ast_node != NULL){
        current->next = malloc(sizeof(asml_formal_arg_t));
        current = current->next;
        ast_list_elem = (char *) ast_node->data;
        current->val = ast_list_elem;
        ast_node = ast_node->next;
    }
    current->next = NULL;
    return result;
}


void send_func_d_to_asml_parser(pfundef fd){
    // pfundef fd = t->params.tletrec.fd;
    // if (fd->free_vars == NULL){
    // // no free variables, a direct call is possible
        asml_function_t *asml_f = malloc(sizeof(asml_function_t));
        asml_f->name = fd->var;
        asml_f->args = string_list_to_asml_args_list(fd->args);
        asml_f->asmt = to_asml_asmt(fd->body);
        asml_parser_create_function(asml_f);
    // } else {
    // // presence of free or global variables in the function definition,
    // // we need to make a closure
    //
    // }
}

asml_asmt_t *lettuple_to_asmlt(ptree t){
/*
 * transforms let (x1 ,..., xn) = y in N
 * into       let x1 = mem(y) in
 *            ...
 *            let xn = mem(y + 4*n) in N
 */
    int i = 0;
    listNode *l_node = t->params.lettuple.l->head;
    asml_asmt_t *first, *current;
    first = malloc(sizeof(asml_asmt_t));
    first->op = (char *)l_node->data;
    first->exp = malloc(sizeof(asml_exp_t));
    first->exp->type = ASML_MEM_READ;
    first->exp->op1 = t->params.lettuple.t1->params.v;
    first->exp->op2 = int_to_str(0);
    first->exp->op3 = NULL;
    current = first;
    l_node = l_node->next;
    while (l_node != NULL){
        i += WORD_SIZE;
        current->next = malloc(sizeof(asml_asmt_t));
        current->next->op = (char *)l_node->data;
        current->next->exp = malloc(sizeof(asml_exp_t));
        current->next->exp->type = ASML_MEM_READ;
        current->next->exp->op1 = t->params.lettuple.t1->params.v;
        current->next->exp->op2 = int_to_str(i);
        current->next->exp->op3 = NULL;
        current = current->next;
        l_node = l_node->next;
    }
    current->next = to_asml_asmt(t->params.lettuple.t2);
    print_asml_asmt(first);
    return first;
}

asml_asmt_t *tuple_to_asml_asmt(ptree t){
    asml_asmt_t *first, *current;
    listNode *l_node = t->params.tlet.t1->params.ttuple.l->head;
    int i = 0;
    first = malloc(sizeof(asml_asmt_t));
    first->op = t->params.tlet.v;
    first->exp = malloc(sizeof(asml_exp_t));
    first->exp->type = ASML_MEM_NEW;
    first->exp->op1 =
        int_to_str(WORD_SIZE * (t->params.tlet.t1->params.ttuple.l->logicalLength));
    first->exp->op2 = NULL; first->exp->op3 = NULL;
    current = first;
    while(l_node != NULL){
        assert((((ptree)l_node->data)->code == T_VAR) ||
                (((ptree)l_node->data)->code == T_INT));
        current->next = malloc(sizeof(asml_asmt_t));
        current->next->op = gen_varname();
        current->next->exp = malloc(sizeof(asml_exp_t));
        current->next->exp->type = ASML_MEM_WRITE;
        current->next->exp->op1 = t->params.tlet.v;
        current->next->exp->op2 = int_to_str(i);
        current->next->exp->op3 = (
            ((ptree)l_node->data)->code == T_VAR ?
            ((ptree)l_node->data)->params.v :
            int_to_str(((ptree)l_node->data)->params.i)
        );
        current = current->next;
        l_node = l_node->next;
        i += WORD_SIZE;
    }
    current->next = to_asml_asmt(t->params.tlet.t2);
    return first;
}

asml_asmt_t *mk_clos_to_asml_asmt(ptree t){
    assert(t->params.tlet.t1->code == T_MK_CLOS);
    plist args_l = t->params.tlet.t1->params.tclosure.l;
    assert(args_l->head);
    assert(is_a_label((char *)args_l->head->data));
    int i = 0;
    char *new_varname;
    asml_asmt_t *first, *current;
    // case -> let x = make_closure(l1, l2, ..., ln) in M
    // allocate a new array
    first = malloc(sizeof(asml_asmt_t));
    first->op = t->params.tlet.v;
    first->exp = malloc(sizeof(asml_exp_t));
    first->exp->type = ASML_MEM_NEW;
    first->exp->op1 = int_to_str(WORD_SIZE * args_l->logicalLength);
    first->exp->op2 = NULL; first->exp->op3 = NULL;
    // store the address of the function label
    current = first;
    listNode *l_node = args_l->head;
    while(l_node != NULL){
        // first we do let new_var = current_arg
        current->next = malloc(sizeof(asml_asmt_t));
        new_varname = gen_varname();
        current->next->op = new_varname;
        current->next->exp = malloc(sizeof(asml_exp_t));
        current->next->exp->type = (
            is_a_label((char *)l_node->data) ?
            ASML_EXP_LABEL :
            ASML_EXP_IDENT
        );
        current->next->exp->op1 = (char *)l_node->data;
        current->next->exp->op2 = NULL; current->next->exp->op3 = NULL;
        current = current->next;
        // then we do let new_var2 = (%self + i*WORD_SIZE) <- new_var
        current->next = malloc(sizeof(asml_asmt_t));
        current->next->op = gen_varname();
        current->next->exp = malloc(sizeof(asml_exp_t));
        current->next->exp->type = ASML_MEM_WRITE;
        current->next->exp->op1 = t->params.tlet.v;
        current->next->exp->op2 = int_to_str(WORD_SIZE * i);
        current->next->exp->op3 = new_varname;
        current = current->next;
        l_node = l_node->next;
        i ++;
    }
    current->next = to_asml_asmt(t->params.tlet.t2);
    return first;
}
