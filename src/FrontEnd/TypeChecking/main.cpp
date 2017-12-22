#include "Ast.hpp"
#include "AstNode.hpp"
#include "AstVisTypeChecking.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return EXIT_FAILURE ;
    }
    try {
        Environment env ;
	Ast ast = Ast(argv[1]) ;
        AstVisitor * TypeChecker = Strategy(Strategy::V_TYPE_CHECKER, &env).setupAstVisitor() ;
        ast.visitAst(TypeChecker) ;
        delete TypeChecker ;
        free_ast(ast.ast) ;
    } catch (std::string const & message) {
	std::cout << message ;
	return EXIT_FAILURE ;
    }
    return EXIT_SUCCESS ;
}
