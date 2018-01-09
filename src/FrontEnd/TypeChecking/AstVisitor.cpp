#include "AstVisitor.hpp"
#include "AstNode.hpp"
#include <iostream>

AstVisitor::AstVisitor(AstVisAbstract *prefix, AstVisAbstract *infix, AstVisAbstract *postfix) :
ind(-1), cpt(0), prefix(prefix), infix(infix), postfix(postfix) {}

AstVisAbstract* AstVisitor::GetPrefix() const {
    return prefix;
}

AstVisAbstract* AstVisitor::GetInfix() const {
    return infix;
}

AstVisAbstract* AstVisitor::GetPostfix() const {
    return postfix;
}

void AstVisitor::setOs(std::ostream* os) {
    this->os = os;
}

std::ostream & AstVisitor::getOs() {
    return *os;
}

AstVisitor::~AstVisitor() {
    delete prefix ;
    delete infix ;
    delete postfix ;
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