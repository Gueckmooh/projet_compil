#include "utils.h"
#include <iostream>
#include "Ast.hpp"

#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstNodeTernary.hpp"
#include "AstVisitor.hpp"

Ast::Ast() : strategy(Strategy()), root(NULL) {}

Ast::Ast(const char* filename) {
    FILE *file = fopen(filename, "r");
    std::string name = filename ;
    std::cout << name << std::endl ;
    if (file == NULL)
        throw std::string("cannot open file " + name + "\n") ;
    std::cout << "OK\n" ;
    ptree ast ;
    yyin = file;
    if (yyparse(&ast))
        throw std::string("parse error\n") ;
    print_term(ast) ;
    std::cout << std::endl ;
    root = build_ast(ast) ;
    free_ast(ast) ;
    std::cout << "FACK!" << std::endl ;
}

AstNode* Ast::build_ast(ptree t){
    assert(t);
    switch(t->code) {
        case T_UNIT :
            return new AstNodeUnit();
        case T_BOOL :
            return new AstNodeBool(t->params.b);
        case T_INT :
            return new AstNodeInt(t->params.i);
        case T_FLOAT :
            return new AstNodeFloat(t->params.f);
        case T_NOT :
            return new AstNodeNot(build_ast(t->params.t));
        case T_NEG :
            return new AstNodeNeg(build_ast(t->params.t));
        case T_FNEG :
            return new AstNodeFneg(build_ast(t->params.t));
        case T_ADD :
            return new AstNodeAdd(build_ast(t->params.tbinary.t1),
                                  build_ast(t->params.tbinary.t2));
        case T_SUB :
            return new AstNodeSub(build_ast(t->params.tbinary.t1),
                                  build_ast(t->params.tbinary.t2));
        case T_FADD :
            return new AstNodeFadd(build_ast(t->params.tbinary.t1),
                                   build_ast(t->params.tbinary.t2));
        case T_FSUB :
            return new AstNodeFsub(build_ast(t->params.tbinary.t1),
                                   build_ast(t->params.tbinary.t2));
        case T_FMUL :
            return new AstNodeFmul(build_ast(t->params.tbinary.t1),
                                   build_ast(t->params.tbinary.t2));
        case T_FDIV :
            return new AstNodeFdiv(build_ast(t->params.tbinary.t1),
                                   build_ast(t->params.tbinary.t2));
        case T_EQ :
            return new AstNodeEq(build_ast(t->params.tbinary.t1),
                                 build_ast(t->params.tbinary.t2));
        case T_LE :
            return new AstNodeLe(build_ast(t->params.tbinary.t1),
                                 build_ast(t->params.tbinary.t2));
        case T_ARRAY :
            return new AstNodeArray(build_ast(t->params.tbinary.t1),
                                    build_ast(t->params.tbinary.t2));
        case T_GET :
            return new AstNodeGet(build_ast(t->params.tbinary.t1),
                                  build_ast(t->params.tbinary.t2));
        case T_IF :
            return new AstNodeIf(build_ast(t->params.tternary.t1),
                                 build_ast(t->params.tternary.t2),
                                 build_ast(t->params.tternary.t3));
        case T_PUT :
            return new AstNodePut(build_ast(t->params.tternary.t1),
                                  build_ast(t->params.tternary.t2),
                                  build_ast(t->params.tternary.t3));
        case T_LET :
            return new AstNodeLet(build_ast(t->params.tlet.t1),
                                  build_ast(t->params.tlet.t2),
                                  to_cpp_string(t->params.tlet.v));
        case T_VAR :
            return new AstNodeVar(to_cpp_string(t->params.v));
        case T_LETREC :
            return new AstNodeLetRec(new FunDef(to_cpp_string(t->params.tletrec.fd->var),
                                        t->params.tletrec.fd->t.code,
                                        to_cpp_str_list(t->params.tletrec.fd->args),    /// TODO <- ici
                                        build_ast(t->params.tletrec.fd->body)
                                       ),
                                        build_ast(t->params.tletrec.t));
        case T_APP :
            return new AstNodeApp(to_cpp_node_list(t->params.tapp.l),                  /// TODO <- ici
                                  build_ast(t->params.tapp.t));
        case T_TUPLE :
            return new AstNodeTuple(to_cpp_node_list(t->params.ttuple.l));             /// TODO <- ici
        case T_LETTUPLE :
            return new AstNodeLetTuple(to_cpp_str_list(t->params.lettuple.l),         /// TODO <- ici
                                       build_ast(t->params.lettuple.t1),
                                       build_ast(t->params.lettuple.t2));
        default:
             printf("Error in build_ast. tree node code = %d\n ", t->code);
             assert(false);
    }
}

Strategy & Ast::getStrategy() {
    return strategy ;
}

AstNode* Ast::getRoot() const {
    return root;
}

Ast::~Ast() {
    if (root != NULL) {
	Strategy strat ;
	strat.setupStrategy(strategy.DESTRUCTOR) ;
	AstVisitor * vis = strat.setupAstVisitor() ;
        root->apply(*vis) ;
        std::cout << "Destruction de l'AST" << std::endl ;
        std::cout << "Nombre de Noeuds Détruits : " << vis->getCounter() << std::endl ;
        root = NULL ;
    }
}

