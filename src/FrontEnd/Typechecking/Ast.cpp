/* 
 * File:   Ast.cpp
 * Author: bleuzeb
 * 
 * Created on 12 décembre 2017, 12:56
 */

#include "Ast.h"
#include <iostream>

Ast::Ast() {
    ast = NULL ;
}

Ast::Ast(const char* nomfich) {
    FILE *file = fopen(nomfich, "r");
    std::string fich = nomfich ;
    std::cout << fich << std::endl ;
    if (file == NULL)
        throw std::string("cannot open file " + fich + "\n") ;
    std::cout << "OK\n" ;
    yyin = file;
    if (yyparse(&ast))
        throw std::string("parse error\n") ;
}
Ast::Ast(const Ast& orig) {
}

Ast::inferer_types() {
    ptree * refast = ast ;
    assert(refast);
    switch (refast->code) {
        case T_UNIT:
            refast->
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
       default:
            printf("%d ", t->code);
            assert(false);
    } 
}

Ast::~Ast() {
}

