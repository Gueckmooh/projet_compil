#ifndef ASTNODE_HPP
#define ASTNODE_HPP

/*********************   CLASS TYPES MACROS***********************************/

#define C_UNDEFINED 0
#define C_UNIT 1
#define C_BOOL 2
#define C_INT 3
#define C_FLOAT 4
#define C_NOT 5
#define C_NEG 6
#define C_ADD 7
#define C_SUB 8
#define C_FNEG 9
#define C_FADD 10
#define C_FSUB 11
#define C_FMUL 12
#define C_FDIV 13
#define C_EQ 14
#define C_LE 15
#define C_IF 16
#define C_LET 17
#define C_VAR 18
#define C_LETREC 19
#define C_APP 20
#define C_TUPLE 21
#define C_LETTUPLE 22
#define C_ARRAY 23
#define C_GET 24
#define C_PUT 25
#define C_FUNDEF 26

#include <string>
#include "Type.hpp"

class AstVisitor ;
class AstVisAbstract ;

class AstNode {
protected:
    int class_code ;
    Type ty ;
public:
    AstNode(int class_code) ;
    AstNode(int class_code, TCode tc) ;
    AstNode(int class_code, TCode tc, std::string var) ;
    Type getType() const ;
    virtual void accept (AstVisAbstract & vis) ;
    void apply(AstVisitor & vis) ;
    virtual void traversal(AstVisitor & vis) = 0 ;
    std::string class_code_to_string() ;
    virtual std::ostream & print(std::ostream& os) ;
    friend std::ostream& operator<<(std::ostream& os, AstNode& node) ;
    virtual ~AstNode() = 0 ;
};

#endif /* ASTNODE_HPP */

