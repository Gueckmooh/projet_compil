#include "AstVisInfer.hpp"
#include <iostream>
#include "Type.hpp"

AstVisInfer::AstVisInfer() :
AstVisPrint(){}

AstVisInfer::~AstVisInfer() {}

void AstVisInfer::print(AstNode& node) {
    if(isCorrectlyTyped(node))
        std::cout << node.getType().print() << node << std::endl ; 
}


bool AstVisInfer::isCorrectlyTyped(AstNode& node) {
    return true ;
}





