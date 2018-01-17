#include "ast.h"
#include "list.h"
#include "print_and_write.h"

#include <stdio.h>
#include <assert.h>

extern plist fd_list;

void print_binary(char *op, ptree t1, ptree t2) {
    printf("(");
    print_term(t1);
    printf(" %s ", op);
    print_term(t2);
    printf(")");
}

void print_id(id i) {
    printf("%s", i);
}

void print_unary(char *op, ptree t) {
    printf("(");
    printf("%s ", op);
    print_term(t);
    printf(")");
}

// precondition: list is not empty
void print_list(plist l, char *sep, void f(void *)) {
    assert(l && !is_empty(l));
    plist cur = l;
    f(head(cur));
    cur = tail(cur);
    while (!is_empty(cur)) {
        printf("%s", sep);
        f(head(cur));
        cur = tail(cur);
    }
}

void print_term(ptree t) {
    assert(t);
    switch (t->code) {
        case T_UNIT:
            printf("()");
            break;
        case T_BOOL:
            printf("%s", t->params.b?"true":"false");
            break;
        case T_INT:
            printf("%d", t->params.i);
            break;
        case T_FLOAT:
            printf("%.2f", t->params.f);
            break;
        case T_LET:
            printf("(");
            printf("let %s = ", t->params.tlet.v);
            print_term( t->params.tlet.t1);
            printf(" in ");
            print_term( t->params.tlet.t2);
            printf(")");
            break;
        case T_VAR:
            printf("%s", t->params.v);
            break;
        case T_ADD:
            print_binary("+",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_SUB:
            print_binary("-",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FADD:
            print_binary("+.",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FSUB:
            print_binary("-.",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FMUL:
            print_binary("*.",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FDIV:
            print_binary("/.",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_LE:
            print_binary("<=",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_EQ:
            print_binary("=",
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_NEG:
            print_unary("-", t->params.t);
            break;
        case T_FNEG:
            print_unary("-.", t->params.t);
            break;
        case T_NOT:
            assert(t->code == T_NOT);
            assert(t->params.t->code != T_NOT);
            print_unary("not", t->params.t);
            break;
        case T_PUT:
            printf("(");
            print_term(t->params.tternary.t1);
            printf(".(");
            print_term(t->params.tternary.t2);
            printf(") <- ");
            print_term(t->params.tternary.t3);
            printf(")");
            break;
        case T_GET:
            print_term(t->params.tbinary.t1);
            printf(".(");
            print_term(t->params.tbinary.t2);
            printf(")");
            break;
        case T_ARRAY:
            printf("(Array.create ");
            print_term(t->params.tbinary.t1);
            printf(" ");
            print_term(t->params.tbinary.t2);
            printf(")");
            break;
        case T_IF:
            printf("(if ");
            print_term(t->params.tternary.t1);
            printf(" then ");
            print_term(t->params.tternary.t2);
            printf(" else ");
            print_term(t->params.tternary.t3);
            printf(")");
            break;
        case T_LETREC:
            printf("(let rec %s ",
                    t->params.tletrec.fd->var);
        print_list(t->params.tletrec.fd->args, " ",
                   (void *)print_id);
            printf(" = ");
            print_term(t->params.tletrec.fd->body);
            printf(" in ");
            print_term(t->params.tletrec.t);
            printf(")");
            break;
         case T_TUPLE:
            printf("(");
            print_list(t->params.ttuple.l, ", ",
                      (void *)print_term);
            // TODO - revoir type
            printf(")");
            break;
         case T_APP:
            printf("(");
            print_term(t->params.tapp.t);
            printf(" ");
            print_list(t->params.tapp.l, " " ,
                      (void *)print_term);
            printf(")");
            break;
         case T_LETTUPLE:
            printf("(let (");
            print_list(t->params.lettuple.l, ", ",
                      (void *)print_id);
            printf(") = ");
            print_term(t->params.lettuple.t1);
            printf(" in ");
            print_term(t->params.lettuple.t2);
            printf(")");
            break;
        case T_MK_CLOS:
            printf("(make_closure(");
            // print_list(t->params.tclosure.l, ",", (void*)print_term);
            // TODO -> revoir type
            print_str_list(t->params.tclosure.l);
            printf("))");
            break;
        case T_APP_CLOS:
            printf("(call_closure(");
            // print_list(t->params.tclosure.l, ",", (void*)print_term);
            // TODO -> revoir type
            print_str_list(t->params.tclosure.l);
            printf("))");
            break;
       default:
            printf("%d \n", t->code);
            assert(false);
    }
}


void print_fd_description(pfundef fd){
    printf("\n    name = %s\n    args = ", fd->var);
    print_str_list(fd->args);
    printf("\n    free vars = ");
    print_str_list(fd->free_vars);
    printf("\n    body = ");
    print_term(fd->body);
    printf("\n");
}

void print_all_fd_descriptions(){
    printf("\nFunctions descriptions :");
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        print_fd_description((pfundef)l_node->data);
        l_node = l_node->next;
    }
}



void print_asml_fun(asml_function_t *t){
    if(t == NULL){
        printf("FUN :( all NULL)\n");
        return;
    }
    printf("FUN : (name = ");
    (t->name == NULL ? printf("NULL ;; args = (") : printf("%s ;; exp = ", (char *)t->name));
    print_asml_fun_args(t->args);
    printf(" ;; asmt =");
    print_asml_asmt(t->asmt);
    printf(")");
}

void print_asml_asmt(asml_asmt_t *t){
    if (t == NULL){
        printf("ASMT :(ALL NULL)");
        return;
    }
    printf("ASMT:(name = ");
    (t->op == NULL ? printf("NULL") : printf("%s", (char *)(char *)t->op));
    printf(" ;; exp = ");
    print_asml_exp(t->exp);
    printf(" ;; next = ");
    print_asml_asmt(t->next);
    printf(")");
}

void print_asml_exp(asml_exp_t *t){
    if (t == NULL){
        printf("EXP : (ALL NULL)");
    }
    printf("EXP:(type = ");
    switch(t->type){
        case ASML_EXP_INT:
            printf("int ;; value = %s", (char *)t->op1);
            break;
        case ASML_EXP_IDENT:
            printf("Ident ;; value = %s", (char *)t->op1);
            break;
        case ASML_EXP_LABEL:
            printf("label ;; value = %s", (char *)t->op1);
            break;
        case ASML_EXP_ADD:
            printf("add ;; op1 = %s, op2 = %s", (char *)t->op1, (char *)t->op2);
            break;
        case ASML_EXP_CALL:
            printf("call : fun name = %s ;; args = (", (char *)t->op1);
            print_asml_fun_args(t->op2);
            printf(")");
            break;
        default:
            printf("type = %d ", t->type);
    }
    printf(")");
}

void print_asml_fun_args(asml_formal_arg_t *t){
    if (!t) return;
    printf(" %s ", (char *)t->val);
    print_asml_fun_args(t->next);
}


void print_str_list(plist l){
    listNode *l_node = l->head;
    while (l_node !=NULL){
        printf("%s", (char *)l_node->data);
        l_node = l_node->next;
        if (l_node) printf(", ");
    }
}

void print_delim_line(){
    printf("\n________________________________________________________"
        "__________________________\n");
}
