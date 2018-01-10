

#include "AstNode.hpp"
#include "AstVisTypeChecking.hpp"
#include "Type.hpp"
#include "TypeFactory.hpp"

#include "type_caller.h"
#include <iostream>
#include <fstream>

#define TYPECHECKING_SUCCESS 0
#define TYPECHECKING_FAILURE 1

// Routine qui applique le TypeChecking du programme

int typeChecking (Ast & ast) {

    /* TYPECHECKING */

    // Initialisation de l'environnement pour le TypeChecking 

    Environment env ; 

    // Mise en place d'une "stratégie" de TypeChecking via la création d'un visiteur "TypeChecker"

    AstVisitor * TypeChecker = Strategy(V_TYPE_CHECKER, &env).setupAstVisitor() ;
    TypeChecker->setOs(&ast.getOs()) ;
    env.setOs(&ast.getOs()) ;

    /* Le TypeChecker se décompose en trois sous-visiteurs  : */
        /* - un sous-visiteur de type AstVisExplore pour le traitement préfixe : */
            // Vérifie que les identificateurs utilisés dans le programme
            // sont bien connus dans les environnements local ou global
            // Renvoie une exception si un identificateur est inconnu des environnements
        /* - un sous-visiteur de type AstVisRangeLet pour le traitement infixe : */
            // Vérifie et calcule le type de l'identificateur introduit par le mot-clé "let"
            // et stocke l'identificateur dans l'environnement local déterminant ainsi sa portée dans le programme
            // Renvoie une exception si le typage de la valeur de l'identificateur est incorrect
        /* - un sous-visiteur de type AstVisInfer pour le traitement postfixe : */
            // Calcule et infère le typage du programme via unification des types des noeuds de l'Ast
            // Renvoie une exception si l'unification des types a échoué

    // Le "TypeChecker" visite l'Ast
    // Si une exception a été attrapée, cela signifie que le programme TypeChecké est incorrectement typé
    // la routine renvoie alors TYPECHECKING_FAILURE (1)

    try {
        ast.visitAst(TypeChecker) ;
    } catch (bool & exception) {
        delete TypeChecker ;
        return TYPECHECKING_FAILURE ;
    }

    // Dans le cas contraire :
    // Vérification du résultat final de l'inférence des types :
    // Le programme est correctement typé si le résultat de l'inférence de types est le type UNIT
    // La routine renvoie alors TYPECHECKING_SUCCESS (0)
    // Elle renvoie TYPECHECKING_FAILURE (1) sinon

    unsigned TypeChecking = ((AstVisInfer*)TypeChecker->GetPostfix())->isWholeProgramCorrectlyTyped() ?
        TYPECHECKING_SUCCESS : TYPECHECKING_FAILURE ;

    TypeChecker->getOs() << "TYPECHECKING " <<
            (TypeChecking == TYPECHECKING_SUCCESS ? "SUCCESS" : "FAILURE")
        << std::endl ;
    
    delete TypeChecker ;
    return TypeChecking ;
}

int init_tc(ptree ptree_ast) {

    
    try {

        /* Création de l'arbre syntaxique abstrait à partir d'un ptree */

        //Ast * ast = new Ast(ptree_ast) ;
        Ast * ast = new Ast(ptree_ast, new std::ofstream("tests/typechecking/TypeChecking.dump")) ;
        
        int TypeChecking = typeChecking(*ast) ;
        delete ast ;
        return TypeChecking ;
        
        
    } catch (std::string const & message) {
        std::cout << message ;
        return EXIT_FAILURE ;
    }
}
