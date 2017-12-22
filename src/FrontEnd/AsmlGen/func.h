    #include <assert.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    #include "list.h"
    #include "knorm.h"
    #include "alpha_conv.h"
    #include "reduce_nested_let.h"



    void print_term(ptree t);

    void print_binary(char *op, ptree t1, ptree t2);

    void print_id(id i);

    void print_unary(char *op, ptree t);

    // precondition: list is not empty
    void print_list(plist l, char *sep, void f(void *)) ;
    void print_term(ptree t) ;

    // BONJOUR JE SUIS DANS LE MAIN
    // SILVOUPLAIT BOUGEZ MOI DANS UNE AUTRE FONCTION
        void write_term(FILE* output,ptree t);

    void write_binary(FILE* output,char *op, ptree t1, ptree t2);

    void write_id(FILE* output,id i);

    void write_unary(FILE* output,char *op, ptree t);
    // precondition: list is not empty
    void write_list(FILE* output,plist l, char *sep, void f(void *));

    void write_term(FILE* output,ptree t) ;


    extern FILE *yyin;
    extern int yydebug;
    extern int yyparse(ptree *ast);


    int parsecall(ptree* p, char* fichier);
    int parseprint(ptree p, char* fichier);
	ptree ast_transform ( ptree p);