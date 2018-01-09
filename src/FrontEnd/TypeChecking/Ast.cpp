#include "utils.h"
#include <iostream>
#include "Ast.hpp"

#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstNodeTernary.hpp"
#include "AstVisitor.hpp"
#include "AstVis.hpp"

Ast::Ast() : os(&std::cout), root(NULL) {}

Ast::Ast(ptree ast) : Ast(ast, &std::cout) {
}

Ast::Ast(ptree ast, std::ostream * os) : os(os) {
    this->ast = ast ;
    root = build_ast(ast) ;
}

Ast::Ast(const char* filename) : Ast(filename, &std::cout) {
    
}

Ast::Ast(const char* filename, std::ostream * os) : os(os) {
    FILE *file = fopen(filename, "r");
    std::string name = filename ;
    if (file == NULL)
        throw std::string("cannot open file " + name + "\n") ;
    ptree ast ;
    yyin = file;
    if (yyparse(&ast))
        throw std::string("parse error\n") ;
    //print_term(ast) ;
    this->ast = ast ;
    root = build_ast(ast) ;
}

std::ostream& Ast::getOs() const {
    return *os;
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
                                                to_cpp_str_list(t->params.tletrec.fd->args),
                                                build_ast(t->params.tletrec.fd->body)
                                                ),
                                         build_ast(t->params.tletrec.t));
        case T_APP :
            return new AstNodeApp(to_cpp_node_list(t->params.tapp.l),
                                  (AstNodeVar*)build_ast(t->params.tapp.t));
        case T_TUPLE :
            return new AstNodeTuple(to_cpp_node_list(t->params.ttuple.l));
        case T_LETTUPLE :
            return new AstNodeLetTuple(to_cpp_str_list(t->params.lettuple.l),
                                       build_ast(t->params.lettuple.t1),
                                       build_ast(t->params.lettuple.t2));
        default:
             printf("Error in build_ast. tree node code = %d\n ", t->code);
             assert(false);
    }
}

void Ast::visitAst(AstVisitor * vis) {
    root->apply(vis) ;
}


Ast::~Ast() {
    if (root != NULL) {
        AstVisitor * destructor = Strategy(V_DESTRUCTOR).setupAstVisitor() ;
        //std::ofstream os ("TypeChecking.dump", std::ios_base::app) ;
        destructor->setOs(os) ;
        visitAst(destructor) ;
        destructor->getOs() << "Nombre de noeuds détruits : " << destructor->getCounter() << std::endl ;
        destructor->getOs() << "Destruction de l'AST" << std::endl ;
        delete destructor ;
        if (os != &std::cout)
            delete os ;
        root = NULL ;
    }
}

