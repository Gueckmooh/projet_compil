#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "AstNode.hpp"
#include "AstVisitor.hpp"
#include <string>

class AstNode;
class AstVisInfer;

class AstVisAbstract {
protected:
    AstVisitor * AstVis ;
public:
    AstVisAbstract();
    void setAstVist(AstVisitor * AstVis);
    virtual void visit_node(AstNode & node) = 0 ;
    virtual ~AstVisAbstract() = 0 ;
};

class AstVisGhost : public AstVisAbstract {
public:
    AstVisGhost();
    void visit_node(AstNode& node) override;
    virtual ~AstVisGhost();
};

class AstVisDestruct : public AstVisAbstract {
public:
    AstVisDestruct();
    void visit_node(AstNode& node) override;
    virtual ~AstVisDestruct();

};

class AstVisPrint : public AstVisAbstract {
public:
    AstVisPrint();
    ~AstVisPrint();
    void visit_node(AstNode& node) override;
    virtual void print (AstNode & node) ;
};

class AstVisitor {
private:
    int ind ;
    int cpt ;
protected:
    AstVisAbstract *prior,  *feedback ;
public:
    const std::string INDENT = "  " ;
    AstVisitor(AstVisAbstract * prior, AstVisAbstract * feedback);
    AstVisAbstract* getPrior() const;
    AstVisAbstract* getFeedBack() const;
    void indent ();
    void unindent ();
    int getIndent () const;
    int getCounter() const;
    void incrCounter() ;
    void resetCounter();
    virtual ~AstVisitor();
};

#endif
