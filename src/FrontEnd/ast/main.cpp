#include "AstNode.hpp"
#include "AstNodeAdd.hpp"
#include "AstNodeApp.hpp"
#include "AstNodeArray.hpp"
#include "AstNodeBool.hpp"
#include "AstNodeEq.hpp"
#include "AstNodeFadd.hpp"
#include "AstNodeFdiv.hpp"
#include "AstNodeFloat.hpp"
#include "AstNodeFmul.hpp"
#include "AstNodeFneg.hpp"
#include "AstNodeFsub.hpp"
#include "AstNodeGet.hpp"
#include "AstNodeIf.hpp"
#include "AstNodeInt.hpp"
#include "AstNodeLe.hpp"
#include "AstNodeLet.hpp"
#include "AstNodeLetRec.hpp"
#include "AstNodeLetTuple.hpp"
#include "AstNodeNeg.hpp"
#include "AstNodeNot.hpp"
#include "AstNodePut.hpp"
#include "AstNodeSub.hpp"
#include "AstNodeTuple.hpp"
#include "AstNodeUnit.hpp"
#include "AstNodeVar.hpp"
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
