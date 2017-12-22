#ifndef AST_VISITOR_H
#define AST_VISITOR_H

#include "AstNode.hpp"
#include <fstream>
#include <iostream>
#include <string>

class AstNode;
class AstVisInfer;
class AstVisitor ;
class AstVisAbstract;

class AstVisitor {
private:
    int ind ;
    int cpt ;
protected:
    AstVisAbstract *prior,  *feedback ;
    //std::ofstream os = std::ofstream("/dev/null") ;
    std::ostream & os = std::cout ;
public:
    const std::string INDENT = "  " ;
    AstVisitor(AstVisAbstract * prior, AstVisAbstract * feedback);
    AstVisAbstract * getPrior() const;
    AstVisAbstract * getFeedBack() const;
    std::ostream & getOs() ;
    void indent ();
    void unindent ();
    int getIndent () const;
    int getCounter() const;
    void incrCounter() ;
    void resetCounter();
    virtual ~AstVisitor();
};

#endif
