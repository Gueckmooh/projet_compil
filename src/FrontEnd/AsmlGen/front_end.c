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
#include "closure.h"
#include "constant_folding.h"
#include "map_var_and_func.h"
#include "inline_expansion.h"
// Global variables
int varname_counter, funcname_counter;
plist fd_list, used_vars, created_vars;

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
        ptree t3 = alpha_convert(t2, init_env());
        print_term(t3);
        printf("\n\nAfter nested let reduction :\n");
        ptree t4 = reduce_nested_let(t3);
        print_term(t4);
        printf("\n\nAfter beta reduction :\n");
        ptree t5 = beta_red(t4, NULL);
        print_term(t5);
        printf("\n\nAfter Constant folding :\n");
        ptree t6 = apply_constant_folding(t5);
        print_term(t6);
        printf("\n\nAfter functions definitions mapping and extraction\n\n");
        fd_list = empty();
        ptree t7 = map_functions(t6, NULL);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t7);
        printf("\n\nAfter removing unnecessary defs :\n");
        ptree t8 = eliminate_unnecessary_defs(t7);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t8);
        printf("\n\nAfter inline expansion :\n");
        ptree t9 = apply_inline_expansion(t8);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t9);
        printf("\n\nAfter closure conversion :\n");
        ptree t10 = apply_closure_conversion(t9);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t10);
        printf("\n\nAST transformation done\n");
        return t10;
    } else {
        ptree t1 = beta_red(reduce_nested_let(alpha_convert(knorm(t), NULL)), NULL);
        return eliminate_unnecessary_defs(apply_constant_folding(t1));
    }
}
