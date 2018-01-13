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
class AstNodeLet;
class AstNodeLetTuple;
class AstNodeSub;

class AstVisAbstract {
private:
    AstVisitor *AstVis ;
public:
    AstVisAbstract();
    AstVisitor * getAstVis () const ;
    void setAstVis(AstVisitor * AstVis);
    
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
    virtual void visit_node(AstNodeLet *let) = 0 ;
    virtual void visit_node(AstNodeLetTuple *lettuple) = 0 ;
    virtual void visit_node(AstNodeSub *sub) = 0 ;
    
    virtual ~AstVisAbstract() = 0 ;
};

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
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    virtual ~AstVisGhost();
};

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
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    virtual ~AstVisDestruct();
};

class AstVisPrint : public AstVisAbstract {
private:
    void print_node_then_new_line(AstNode* node);
protected:
    virtual void print (AstNode * node) ;
public:
    AstVisPrint();
    
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
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    ~AstVisPrint();
};

#endif /* ASTVIS_HPP */

