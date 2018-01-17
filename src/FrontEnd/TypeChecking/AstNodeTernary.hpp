/**
 * \file      AstNodeTernary.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of Ast ternary node
 *
 */

#ifndef AST_NODE_TERNARY_H
#define AST_NODE_TERNARY_H

#include "AstNode.hpp"


class AstNode ;

/* ! 
 * \class AstNodeTernary
 * \brief Abstract Class for Ast ternary nodes definition
 */

class AstNodeTernary : public AstNode {
protected:
    AstNode *t1, *t2, *t3 ; /* ! < left child t1, middle child t2, right child t3 */
public:
    /* !
     * \brief Constructor
     * \params int class_code, AstNode* t1, AstNode* t2, AstNode* t3
     */
    AstNodeTernary(int class_code, AstNode *t1, AstNode *t2, AstNode *t3);
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeTernary() = 0 ;
};

/* ! 
 * \class AstNodeIf
 * \brief if then else node
 */

class AstNodeIf : public AstNodeTernary {
public:
    Type * type = NULL ; /*< if then else expression type */
    /* !
     * \brief Constructor
     * \params AstNode* t1, AstNode* t2, AstNode* t3
     */
    AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeIf();
};

/* ! 
 * \class AstNodePut
 * \brief "<-" operator to set an element into an array
 */

class AstNodePut : public AstNodeTernary {
public:
    /* !
     * \brief Constructor
     * \params AstNode* t1, AstNode* t2, AstNode* t3
     */
    AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3);
    void accept(AstVisAbstract* vis) override;
    ~AstNodePut();
};

#endif
