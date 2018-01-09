#include "Ast.hpp"
#include "AstNode.hpp"
#include "AstVisTypeChecking.hpp"
#include "Type.hpp"
#include "TypeFactory.hpp"
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
        free_ast(ast.ast) ;
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
    free_ast(ast.ast) ;

    return TypeChecking ;
}

// Test de la fabrique de types simples, applications et tuples

/*static void test_types() {
    Type * types[4] ;
    types[0] = TypeSimpleFactory(FLOAT).create() ;
    std::cout << *types[0] << std::endl ;
    types[1] = new Type(TypeTupleFactory({{Simple,FLOAT},{Simple,INT},{Simple,FLOAT},{Simple,UNIT}}).create()) ;
    types[2] = new Type(TypeAppFactory({{Simple,FLOAT},{Simple,INT},{Simple,FLOAT},{Simple,UNIT}}).create()) ;
    std::cout << *types[1] << std::endl ;
    std::cout << *types[2] << std::endl ;
    std::cout << (Type::isCorrectlyTyped(types[1], types[2]) ? "true" : "false")  << std::endl ;
    std::cout << (Type::isCorrectlyTyped(types[1], types[0]) ? "true" : "false")  << std::endl ;
    std::cout << (Type::isCorrectlyTyped(types[1], types[1]) ? "true" : "false")  << std::endl ;
    std::cout << (Type::isCorrectlyTyped(types[2], types[2]) ? "true" : "false")  << std::endl ;
    types[3] = new Type(TypeAppFactory(
    {{Simple,FLOAT},
    {Tuple, TypeTupleFactory({
        {Simple,FLOAT},
        {Simple,INT},
        {Simple,BOOL},
        {Simple,UNIT}
    }).create()},
    {Application, TypeAppFactory({
        {Simple,FLOAT},
        {Simple,INT},
        {Simple,BOOL},
        {Simple,UNIT}
    }).create()},
    {Simple, UNIT}}
    ).create()) ;
    types[3] = TypeFactory({types[0],types[1],types[2],types[3], TypeSimpleFactory(UNIT).create()}).create() ;
    std::cout << *types[3] << std::endl ;
    std::cout << (Type::isCorrectlyTyped(types[3], types[3]) ? "true" : "false")  << std::endl ;
    Type::deleteType(types[3]) ;
}*/

/*void test_print_ast () {

    AstVisitor * Printer = Strategy(V_PRINTER).setupAstVisitor() ;
    ast.visitAst(Printer) ;
    delete Printer ;
    std::cout << "\nTypeChecking :\n\n" ;
    
}*/

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s filename\n", argv[0]);
        return EXIT_FAILURE ;
    }
    
    try {

        /* Création de l'arbre syntaxique abstrait à partir d'un fichier */
        //Ast * ast = new Ast(argv[1]);
        Ast * ast = new Ast(argv[1], new std::ofstream("TypeChecking.dump")) ;
        
        /* Création de l'arbre syntaxique abstrait à partir d'un ptree */

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