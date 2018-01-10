#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "list.h"
#include "knorm.h"
#include "alpha_conv.h"
#include "reduce_nested_let.h"
#include "front_end.h"
#include "print_and_write.h"
#include "beta_red.h"

// Global variables
int varname_counter, funcname_counter;

extern FILE *yyin;
extern int yydebug;
extern int yyparse(ptree *ast);


int parsecall(ptree* p, char* fichier){
    FILE *file;

    file = fopen(fichier,"r");
    yyin = file;
    if (file == NULL){
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier");
        return 1;
    }

    if (yyparse(p) != 0){
        fprintf(stderr,"Erreur : Parsing Error");
        return 1;
    }

    return 0;

}

int parseprint(ptree p, char* fichier){
    FILE *file;
    file = fopen(fichier,"w");
    if (file == NULL){
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier");
        return 1;
    }
    if (p == NULL){
        fprintf(stderr,"Erreur : Pointeur arbre nul");
    }
    print_term(p);
    //write_term(file,p);
    return 0;

}

ptree ast_transform(ptree t){
    varname_counter = 0;
    funcname_counter = 0;
    if (PRINT_AST_STEP_BY_STEP){
        printf("\nAST transformation\nOriginal ast :\n");
        print_term(t);
        printf("\n\nAfter Knormalisation :\n");
        ptree t2 = knorm(t);
        print_term(t2);
        printf("\n\nAfter alpha conversion :\n");
        ptree t3 = alpha_convert(t2, NULL);
        print_term(t3);
        printf("\n\nAfter nested let reduction :\n");
        ptree t4 = reduce_nested_let(t3);
        print_term(t4);
        printf("\n\nAfter beta reduction :\n");
        ptree t5 = beta_red(t4, NULL);
        print_term(t5);
        printf("\n\nAST transformation done\n");
        return t5;
    } else {
        return beta_red(reduce_nested_let(alpha_convert(knorm(t), NULL)), NULL);
    }
}
