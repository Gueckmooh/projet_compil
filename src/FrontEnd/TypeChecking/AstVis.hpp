#ifndef ASTVIS_HPP
#define ASTVIS_HPP

#include <fstream>

class AstVisitor;
class AstNode;
class AstNodeInt;
class AstNodeNeg;
class AstNodeVar;
class AstNodeLet;
class AstNodeApp;
class AstNodeAdd;

class AstVisAbstract {
private:
    AstVisitor *AstVis ;
public:
    AstVisAbstract();
    AstVisitor * getAstVis () const ;
    void setAstVis(AstVisitor * AstVis);
    virtual void visit_node(AstNode* node) = 0 ;
    virtual void visit_node(AstNodeInt *integer) = 0 ;
    virtual void visit_node(AstNodeNeg *neg) = 0 ;
    virtual void visit_node(AstNodeVar *var) = 0 ;
    virtual void visit_node(AstNodeLet *let) = 0 ;
    virtual void visit_node(AstNodeApp *app) = 0 ;
    virtual void visit_node(AstNodeAdd *add) = 0 ;
    virtual ~AstVisAbstract() = 0 ;
};

class AstVisGhost : public AstVisAbstract {
public:
    AstVisGhost();
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeNeg* neg) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeApp* app) override;
    virtual ~AstVisGhost();
};

class AstVisDestruct : public AstVisAbstract {
public:
    AstVisDestruct();
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeNeg* neg) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeApp* app) override;
    virtual ~AstVisDestruct();
};

class AstVisPrint : public AstVisAbstract {
private:
    void print_node_then_new_line(AstNode* node);
protected:
    virtual void print (AstNode * node) ;
public:
    AstVisPrint();
    void visit_node(AstNode* node) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeNeg* neg) override;
    void visit_node(AstNodeVar* var) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeApp* app) override;
    ~AstVisPrint();
};

#endif /* ASTVIS_HPP */

