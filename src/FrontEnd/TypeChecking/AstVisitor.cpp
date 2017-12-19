#include "AstVisitor.hpp"
#include "AstNode.hpp"
#include <cstdlib>
#include <iostream>

AstVisitor::AstVisitor(AstVisAbstract * prior, AstVisAbstract * feedback) :
ind(-1), cpt(0), prior(prior), feedback(feedback) {}


AstVisAbstract* AstVisitor::getFeedBack() const {
    return feedback;
}

AstVisAbstract* AstVisitor::getPrior() const {
    return prior;
}

AstVisitor::~AstVisitor() {
    delete prior ;
    delete feedback ;
}

void AstVisitor::indent() {
    ind++;
}

void AstVisitor::unindent() {
    ind--;
}

int AstVisitor::getIndent() const {
    return ind ;
}

int AstVisitor::getCounter() const {
    return cpt;
}

void AstVisitor::incrCounter() {
    cpt++ ;
}

void AstVisitor::resetCounter() {
    cpt = 0;
}

// Abstract Visitor

AstVisAbstract::AstVisAbstract() :
AstVis(NULL) {}
void AstVisAbstract::setAstVist(AstVisitor* AstVis) { this->AstVis = AstVis ; }

AstVisAbstract::~AstVisAbstract(){}

// Ghost Visitor

AstVisGhost::AstVisGhost() :
AstVisAbstract() {}
inline void AstVisGhost::visit_node(AstNode& node) {}
AstVisGhost::~AstVisGhost() {}


// Destructor Visitor

AstVisDestruct::AstVisDestruct() :
AstVisAbstract() {}
inline void AstVisDestruct::visit_node(AstNode& node) { delete &node ; }
AstVisDestruct::~AstVisDestruct() {}

// Printer Visitor

AstVisPrint::AstVisPrint() :
AstVisAbstract() {}
void AstVisPrint::visit_node(AstNode & node) {
    for (int i = 0 ; i < AstVis->getIndent() ; i++) {
        std::cout << AstVis->INDENT ;
    }
    print(node) ;
}

void AstVisPrint::print(AstNode & node) {
    std::cout << node.class_code_to_string() << node << std::endl;
}


AstVisPrint::~AstVisPrint() {}