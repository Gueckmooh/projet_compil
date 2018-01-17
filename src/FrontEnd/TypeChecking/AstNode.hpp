/**
 * \file      AstNode.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of Ast node
 *
 */

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
#include "AstVis.hpp"

class AstVisitor ;
class AstVisAbstract ;
class Type;

using std::string ;

/* ! 
 * \class AstNode
 * \brief Abstract Class for Ast nodes definition
 */

class AstNode {
protected:
    int class_code ; /*!< class_code to identify Node Class */
    /* !
     *  \brief Node printing
     *  \params ostream & os
     *  \return ostream &
     */
    virtual std::ostream & print(std::ostream& os) ;
public:
    /* !
     * \brief Constructor
     *  \params class code of Node
     */
    AstNode(int class_code) ;
    /* !
     * \brief  pure virtual method accept for AstVisitor
     *  \params AstVisitor
     */
    virtual void accept (AstVisAbstract * vis) = 0 ;
    /* !
     * \brief  pure virtual method of iteration for AstVisitor run through
     *  \params AstVisitor
     */
    virtual void traversal(AstVisitor * vis) = 0 ;
    /* !
     * \brief  method for AstNode processing
     *  \params AstVisitor
     */
    void apply(AstVisitor * vis) ;
    /* !
     * \brief  Class Node printing
     *  \return string of class code
     */
    std::string class_code_to_string() ;
    /* !
     * \brief Constructor
     *  \params class code of Node
     */
    friend std::ostream& operator<<(std::ostream& os, AstNode& node) ;
    /* !
     * \brief pure virtual Node Destructor
     * 
     */
    virtual ~AstNode() = 0 ;
};

#endif /* ASTNODE_HPP */

