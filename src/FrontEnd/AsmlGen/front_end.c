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
    fd_list = empty();
    if (PRINT_AST_STEP_BY_STEP){
        printf("\nAST transformation\nOriginal ast :\n");
        print_term(t);
        print_delim_line();
        printf("\n\nAfter Knormalisation :\n");
        ptree t2 = knorm(t);
        print_term(t2);
        print_delim_line();
        printf("\n\nAfter alpha conversion :\n");
        ptree t3 = alpha_convert(t2, init_env());
        print_term(t3);
        print_delim_line();
        printf("\n\nAfter nested let reduction :\n");
        ptree t4 = reduce_nested_let(t3);
        print_term(t4);
        print_delim_line();
        printf("\n\nAfter beta reduction :\n");
        ptree t5 = beta_red(t4, NULL);
        print_term(t5);
        print_delim_line();
        printf("\n\nAfter Constant folding :\n");
        ptree t6 = apply_constant_folding(t5);
        print_term(t6);
        print_delim_line();
        printf("\n\nAfter functions definitions mapping and extraction\n\n");
        ptree t7 = map_functions(t6, NULL);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t7);
        print_delim_line();
        printf("\n\nAfter removing unnecessary defs :\n");
        ptree t8 = eliminate_unnecessary_defs(reduce_nested_let(t7));
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t8);
        print_delim_line();
        printf("\n\nAfter inline expansion :\n");
        ptree t9 = apply_inline_expansion(t8);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t9);
        print_delim_line();
        printf("\n\nAfter closure conversion :\n");
        ptree t10 = apply_closure_conversion(t9);
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t10);
        print_delim_line();
        printf("\n\nAfter final modifications :\n");
        ptree t11 = reduce_nested_let(knorm(t10));
        listNode *l_node = fd_list->head;
        while(l_node != NULL){
            pfundef fd = (pfundef)l_node->data;
            fd->body = reduce_nested_let(apply_constant_folding(
                            reduce_nested_let(knorm(fd->body))
                        ));
            l_node = l_node->next;
        }
        print_all_fd_descriptions();
        printf("\nProgram :\n");
        print_term(t11);
        printf("\n\nAST transformation done\n");
        return reduce_nested_let(apply_constant_folding(t11));
    } else {
        ptree t2 = knorm(t);
        ptree t3 = alpha_convert(t2, init_env());
        ptree t4 = reduce_nested_let(t3);
        ptree t5 = beta_red(t4, NULL);
        ptree t6 = apply_constant_folding(t5);
        ptree t7 = map_functions(t6, NULL);
        ptree t8 = eliminate_unnecessary_defs(reduce_nested_let(t7));
        ptree t9 = apply_inline_expansion(t8);
        ptree t10 = apply_closure_conversion(t9);
        ptree t11 = reduce_nested_let(t10);
        listNode *l_node = fd_list->head;
        while(l_node != NULL){
            pfundef fd = (pfundef)l_node->data;
            fd->body = reduce_nested_let(apply_constant_folding(
                            reduce_nested_let(knorm(fd->body))
                        ));
            l_node = l_node->next;
        }
        return reduce_nested_let(apply_constant_folding(t11));
    }
}

ptree b4_tc (ptree t){
	return alpha_convert(knorm(t),init_env());
}
