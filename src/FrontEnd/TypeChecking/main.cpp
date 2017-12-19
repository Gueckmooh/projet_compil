#include "Ast.hpp"
#include "AstNode.hpp"
#include "AstVisInfer.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return EXIT_FAILURE ;
    }
    try {
	Ast ast = Ast(argv[1]) ;
        ast.getStrategy().setupStrategy(ast.getStrategy().PRINTER) ;
        ast.getRoot()->apply(*ast.getStrategy().setupAstVisitor()) ;
        std::cout << ast.getStrategy().getAstVis()->getCounter() << std::endl ;
        ast.getStrategy().getAstVis()->resetCounter() ;
        ast.getStrategy().setupStrategy(ast.getStrategy().INFERATOR) ;
        ast.getRoot()->apply(*ast.getStrategy().setupAstVisitor()) ;
    } catch (std::string const & message) {
	std::cout << message ;
	return EXIT_FAILURE ;
    }
    return EXIT_SUCCESS ;
}
