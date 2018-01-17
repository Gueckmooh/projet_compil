/**
 * \file      AstNode.cpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of Ast node
 *
 */


#include "AstNode.hpp"
#include "AstVisitor.hpp"
#include "AstVis.hpp"
#include "Type.hpp"
#include <assert.h>

AstNode::AstNode(int class_code) :
class_code(class_code) {}

void AstNode::apply(AstVisitor * vis) {
    vis->incrCounter() ;
    vis->indent() ;
    accept(vis->GetPrefix()) ;
    traversal(vis) ;
    accept(vis->GetPostfix()) ;
    vis->unindent() ;
}

std::string AstNode::class_code_to_string() {
    
    switch (class_code) {
        case C_UNDEFINED :
            return "UNDEFINED" ;
        case C_UNIT :
            return "UNIT" ;
        case C_BOOL :
            return "BOOL" ;
        case C_INT :
            return "INT" ;
        case C_FLOAT :
            return "FLOAT" ;
        case C_NOT :
            return "NOT" ;
        case C_NEG :
            return "NEG" ;
        case C_ADD :
            return "PLUS" ;
        case C_SUB :
            return "SUB" ;
        case C_FNEG :
            return "FNEG" ;
        case C_FADD :
            return "FADD" ;
        case C_FSUB :
            return "FSUB" ;
        case C_FMUL :
            return "FMUL" ;
        case C_FDIV :
            return "FDIV" ;
        case C_EQ :
            return "EQ" ;
        case C_LE :
            return "LE" ;
        case C_IF :
            return "IF" ;
        case C_LET :
            return "LET" ;
        case C_VAR :
            return "VAR" ;
        case C_LETREC :
            return "LET REC" ;
        case C_APP :
            return "APP" ;
        case C_TUPLE :
            return "TUPLE" ;
        case C_LETTUPLE :
            return "LET TUPLE" ;
        case C_ARRAY :
            return "ARRAY" ;
        case C_GET :
            return "GET" ;
        case C_PUT :
            return "PUT" ;
        case C_FUNDEF :
            return "FUNDEF" ;
    }
    assert(false) ;
}

std::ostream& AstNode::print(std::ostream& os) { return os ; }

std::ostream& operator<<(std::ostream& os, AstNode& node) {
    return node.print(os);
}

AstNode::~AstNode() {}
