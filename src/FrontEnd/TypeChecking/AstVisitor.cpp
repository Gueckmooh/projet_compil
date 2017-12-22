#include "AstVisitor.hpp"
#include "AstNode.hpp"
#include <iostream>

AstVisitor::AstVisitor(AstVisAbstract * prior, AstVisAbstract * feedback) :
ind(-1), cpt(0), prior(prior), feedback(feedback) {}


AstVisAbstract * AstVisitor::getFeedBack() const {
    return feedback;
}

AstVisAbstract * AstVisitor::getPrior() const {
    return prior;
}

std::ostream & AstVisitor::getOs() {
    return os;
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