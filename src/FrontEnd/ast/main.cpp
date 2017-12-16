#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstNodeTernary.hpp"
#include "AstVisitor.hpp"
#include "AstVisPrint.hpp"

#include <assert.h>
#include <stdio.h>
#include "ast.h"
#include "list.h"
#include <iostream>
#include <cstdlib>
extern "C" {
#include "parser.h"
}

extern FILE *yyin;
extern int yydebug;
extern int yyparse(ptree *ast);

int main(int argc, char **argv) {
	FILE *file;
    if (argc != 2) {
        printf("usage: %s file name\n", argv[0]);
        return 0;
    }
	file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("cannot open file %s\n", argv[1]);
        return 0;
    }
    yyin = file;

    // yydebug = 1;
    ptree p;
    if (yyparse(&p) != 0) {
        printf("parse error");
        return 0;
    }
    AstNode * ast_obj = build_ast(p);
    AstVisitor *printer = new AstVisPrint();
    ast_obj->traversal(printer);
    return 0;
}
