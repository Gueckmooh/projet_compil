#include "AstVisPrint.hpp"
#include "AstVisitor.hpp"
#include "FunDef.hpp"
#include "AstNode.hpp"
#include <iostream>

AstVisPrint::AstVisPrint(){
    this->next = NULL;
    this->indent = -1;
}

AstVisPrint::AstVisPrint(AstVisitor *next){
    this->next = next;
    this->indent = -1;
}

AstVisPrint::~AstVisPrint(){}


void AstVisPrint::visit_node(AstNode *node){
/*    this->indent ++;
    int i;
    switch(node->class_code){
        case C_UNIT :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            node->print();
        case C_BOOL :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            node->print();
        case C_INT :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << node->i << "\n" << std::endl;
        case C_FLOAT :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << node->f<< "\n" << std::endl;
        case C_NOT :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "NOT\n"<< std::endl;
        case C_NEG :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "MINUS\n"<< std::endl;
        case C_ADD :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "PLUS\n"<< std::endl;
        case C_SUB :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "SUBSTRACT\n"<< std::endl;
        case C_FNEG :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "MINUS(F)\n"<< std::endl;
        case C_FADD :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "PLUS(F)\n"<< std::endl;
        case C_FSUB :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "SUBSTRACT(F)\n"<< std::endl;
        case C_FMUL :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "MULT(F)\n"<< std::endl;
        case C_FDIV :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "DIV(F)\n"<< std::endl;
        case C_EQ :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "EQUALS\n"<< std::endl;
        case C_LE :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "LESS OR EQUAL\n"<< std::endl;
        case C_IF :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "IF ... THEN ... ELSE\n"<< std::endl;
        case C_LET :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "LET ... IN \n"<< std::endl;
        case C_VAR :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "VAR\n"<< std::endl;
        case C_LETREC :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "LETREC\n"<< std::endl;
        case C_APP :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "APP\n"<< std::endl;
        case C_TUPLE :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "TUPLE\n"<< std::endl;
        case C_LETTUPLE :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "LETTUPLE\n"<< std::endl;
        case C_ARRAY :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "ARRAY\n"<< std::endl;
        case C_GET :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "GET\n"<< std::endl;
        case C_PUT :
            for (i = 0 ; i < indent ; i++) std::cout << INDENT;
            std::cout << "PUT\n"<< std::endl;
        default :
    }
    this->indent --;
    */
}

void AstVisPrint::visit_fun_def(FunDef * fun_def){
    for (int i = 0 ; i < indent ; i++) std::cout << INDENT;
    std::cout <<"FUNDEF" << std::endl;
}
