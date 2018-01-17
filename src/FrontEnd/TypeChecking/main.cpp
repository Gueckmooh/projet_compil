/**
 * \file      main.cpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     TypeChecking launcher
 *
 */

#include "Ast.hpp"
#include "AstNode.hpp"
#include "AstVisTypeChecking.hpp"
#include "Type.hpp"
#include "TypeFactory.hpp"
#include <iostream>
#include <fstream>

#define TYPECHECKING_SUCCESS 0
#define TYPECHECKING_FAILURE 1

// TypeChecking Routine

int typeChecking (Ast & ast) {

    /* TYPECHECKING */

    // Environment Initialization

    Environment env ; 

    // Setting Up TypeChecker

    AstVisitor * TypeChecker = Strategy(V_TYPE_CHECKER, &env).setupAstVisitor() ;
    TypeChecker->setOs(&ast.getOs()) ;
    env.setOs(&ast.getOs()) ;
    TypeSimple::setOs(&ast.getOs()) ;
    
    // programm TypeChecking

    try {
        ast.visitAst(TypeChecker) ;
    } catch (bool & exception) {
        
        // Catch of possible exceptions in case of incorrectly types programm
        
        TypeChecker->getOs() << "TYPECHECKING FAILURE" << std::endl ;
        delete TypeChecker ;
        free_ast(ast.ast) ;
        return TYPECHECKING_FAILURE ;
    }

    // if no exception has been caught, that means the final type of the programm has been computed
    // This final type must be of Type UNIT. Otherwise, that means the programm has computed an expression
    // without side effect, so that means the programm does not change the memory and consequently,
    // does absolutely nothing. It return TYPECHECKING_FAILURE(1) in this case.
    // Otherwise, it returns TYPECHECKING_SUCCESS(0) : The programm is correcly typed.

    unsigned TypeChecking = ((AstVisInfer*)TypeChecker->GetPostfix())->isWholeProgramCorrectlyTyped() ?
        TYPECHECKING_SUCCESS : TYPECHECKING_FAILURE ;

    TypeChecker->getOs() << "TYPECHECKING " <<
            (TypeChecking == TYPECHECKING_SUCCESS ? "SUCCESS" : "FAILURE")
        << std::endl ;
    
    delete TypeChecker ;
    free_ast(ast.ast) ;

    return TypeChecking ;
}



int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return EXIT_FAILURE ;
    }
    
    try {

        // Ast Building from a file
        Ast * ast = new Ast(argv[1], new std::ofstream("TypeChecking.dump")) ;
        
        // Ast Building from a ptree

        //Ast * ast = Ast(ptree_ast) ;
        //Ast * ast = new Ast(ptree_ast, new std::ofstream("TypeChecking.dump")) ;
        
        int TypeChecking = typeChecking(*ast) ;
        delete ast ;
        return TypeChecking ;
        
    } catch (std::string const & message) {
        std::cout << message ;
        return EXIT_FAILURE ;
    }
}
