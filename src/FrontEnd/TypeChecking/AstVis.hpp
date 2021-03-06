/*
 * \file      AstVis.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of secondary Visitors to print and destruct the Ast
 * \details
 * This file defines secondary AstVisitor especially for printing and destruction Ast
 * repectively named AstVisPrint and AstVisDestruct.
 * A third visitor named AstVisGhost is a special visitor processing absolutely nothing
 * This Visitor is used when a prefix,infix or postfix process must be null
 */


#ifndef ASTVIS_HPP
#define ASTVIS_HPP

#include <fstream>

class AstVisitor;

// Node

class AstNode;

// Leaves

class AstNodeBool;
class AstNodeFloat;
class AstNodeInt;
class AstNodeTuple;
class AstNodeUnit;
class AstNodeVar;

// Unary Nodes

class AstNodeApp;
class FunDef;
class AstNodeLetRec;
class AstNodeNeg;

// Binary Nodes

class AstNodeAdd;
class AstNodeLe;
class AstNodeLet;
class AstNodeLetTuple;
class AstNodeSub;

// Ternary Nodes

class AstNodeIf;

/* !
 * \class AstVisAbstract
 */

class AstVisAbstract {
private:
    AstVisitor *AstVis ;
public:
    AstVisAbstract();
    AstVisitor * getAstVis () const ;
    void setAstVis(AstVisitor * AstVis);
    
    // Visit methods
    
    // Node
    
    virtual void visit_node(AstNode* node) = 0 ;
    
    // Leaves
    
    virtual void visit_node(AstNodeBool *boolean) = 0 ;
    virtual void visit_node(AstNodeFloat *floatingpoint) = 0 ;
    virtual void visit_node(AstNodeInt *integer) = 0 ;
    virtual void visit_node(AstNodeTuple *tuple) = 0 ;
    virtual void visit_node(AstNodeUnit* unit) = 0 ;
    virtual void visit_node(AstNodeVar *var) = 0 ;
    
    // Unary Nodes
    
    virtual void visit_node(AstNodeApp *app) = 0 ;
    virtual void visit_node(FunDef *fundef) = 0 ;
    virtual void visit_node(AstNodeLetRec *letrec) = 0 ;
    virtual void visit_node(AstNodeNeg *neg) = 0 ;
    
    // Binary Nodes
    
    virtual void visit_node(AstNodeAdd *add) = 0 ;
    virtual void visit_node(AstNodeLe *le) = 0 ;
    virtual void visit_node(AstNodeLet *let) = 0 ;
    virtual void visit_node(AstNodeLetTuple *lettuple) = 0 ;
    virtual void visit_node(AstNodeSub *sub) = 0 ;
    
    // Ternary Nodes
    
    virtual void visit_node(AstNodeIf *ite) = 0 ;
    
    virtual ~AstVisAbstract() = 0 ;
};

/* !
 * \class AstVisGhost
 */

class AstVisGhost : public AstVisAbstract {
public:
    AstVisGhost();
    
    // Node
    
    void visit_node(AstNode* node) override;
    
    // Leaves
    
    void visit_node(AstNodeBool* boolean) override;
    void visit_node(AstNodeFloat* floatingpoint) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeTuple* tuple) override;
    void visit_node(AstNodeUnit* unit) override;
    void visit_node(AstNodeVar* var) override;
    
    // Unary Nodes
    
    void visit_node(AstNodeApp* app) override;
    void visit_node(FunDef *fundef) override;
    void visit_node(AstNodeLetRec *letrec) override;
    void visit_node(AstNodeNeg* neg) override;
    
    // Binary Nodes
    
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeLe *le) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    // Ternary Nodes
    
    void visit_node(AstNodeIf *ite) override;
    
    
    virtual ~AstVisGhost();
};

/* !
 * \class AstVisDestruct
 */

class AstVisDestruct : public AstVisAbstract {
public:
    AstVisDestruct();
    
    // Node
    
    void visit_node(AstNode* node) override;
    
    // Leaves
    
    void visit_node(AstNodeBool* boolean) override;
    void visit_node(AstNodeFloat* floatingpoint) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeTuple* tuple) override;
    void visit_node(AstNodeUnit* unit) override;
    void visit_node(AstNodeVar* var) override;
    
    // Unary Nodes
    
    void visit_node(AstNodeApp* app) override;
    void visit_node(FunDef *fundef) override;
    void visit_node(AstNodeLetRec *letrec) override;
    void visit_node(AstNodeNeg* neg) override;
    
    // Binary Nodes
    
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeLe *le) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    // Ternary Nodes
    
    void visit_node(AstNodeIf *ite) override;
    
    virtual ~AstVisDestruct();
};

/* !
 * \class AstVisPrint
 */

class AstVisPrint : public AstVisAbstract {
private:
    void print_node_then_new_line(AstNode* node);
protected:
    virtual void print (AstNode * node) ;
public:
    AstVisPrint();
    void printIndent() ;
    // Node
    
    void visit_node(AstNode* node) override;
    
    // Leaves
    
    void visit_node(AstNodeBool* boolean) override;
    void visit_node(AstNodeFloat* floatingpoint) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeTuple* tuple) override;
    void visit_node(AstNodeUnit* unit) override;
    void visit_node(AstNodeVar* var) override;
    
    // Unary Nodes
    
    void visit_node(AstNodeApp* app) override;
    void visit_node(FunDef *fundef) override;
    void visit_node(AstNodeLetRec *letrec) override;
    void visit_node(AstNodeNeg* neg) override;
    
    // Binary Nodes
    
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeLe *le) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    // Ternary Nodes
    
    void visit_node(AstNodeIf *ite) override;
    
    ~AstVisPrint();
};

#endif /* ASTVIS_HPP */

