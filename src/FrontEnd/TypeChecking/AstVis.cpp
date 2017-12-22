#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstVis.hpp"
#include "AstVisitor.hpp"
#include <iostream>
#include <fstream>

// Abstract Visitor

AstVisAbstract::AstVisAbstract() :
AstVis(NULL) {}

AstVisitor* AstVisAbstract::getAstVis() const {
    return AstVis ;
}

void AstVisAbstract::setAstVis(AstVisitor * AstVis) {
    this->AstVis = AstVis ;
}

AstVisAbstract::~AstVisAbstract() {}

// Ghost Visitor

AstVisGhost::AstVisGhost() :
AstVisAbstract() {}
inline void AstVisGhost::visit_node(AstNode* node) {}
inline void AstVisGhost::visit_node(AstNodeInt* integer) {}
inline void AstVisGhost::visit_node(AstNodeVar* var) {}
inline void AstVisGhost::visit_node(AstNodeLet* let) {}
inline void AstVisGhost::visit_node(AstNodeApp* app) {}
inline void AstVisGhost::visit_node(AstNodeAdd* add) {}


AstVisGhost::~AstVisGhost() {}


// Destructor Visitor

AstVisDestruct::AstVisDestruct() :
AstVisAbstract() {}
inline void AstVisDestruct::visit_node(AstNode* node) { delete node ; }
inline void AstVisDestruct::visit_node(AstNodeInt* integer) { delete integer ; }
inline void AstVisDestruct::visit_node(AstNodeVar* var) { delete var ; }
inline void AstVisDestruct::visit_node(AstNodeLet* let) { delete let ; }
inline void AstVisDestruct::visit_node(AstNodeApp* app) { delete app ; }
inline void AstVisDestruct::visit_node(AstNodeAdd* add) { delete add ; }

AstVisDestruct::~AstVisDestruct() {}

// Printer Visitor

AstVisPrint::AstVisPrint() :
AstVisAbstract() {}

void AstVisPrint::visit_node(AstNode * node) {
    print_node_then_new_line(node) ;
}

void AstVisPrint::visit_node(AstNodeInt * integer) {
    print_node_then_new_line(integer) ;
}

void AstVisPrint::visit_node(AstNodeLet * let) {
    print_node_then_new_line(let) ;
}

void AstVisPrint::visit_node(AstNodeVar* var) {
    print_node_then_new_line(var) ;
}

void AstVisPrint::visit_node(AstNodeApp* app) {
    print_node_then_new_line(app) ;
}

void AstVisPrint::visit_node(AstNodeAdd* add) {
    print_node_then_new_line(add) ;
}

void AstVisPrint::print(AstNode * node) {
    for (int i = 0 ; i < getAstVis()->getIndent() ; i++) {
        getAstVis()->getOs() << getAstVis()->INDENT ;
    }
    getAstVis()->getOs() << node->class_code_to_string() + " " << *node ;
}

void AstVisPrint::print_node_then_new_line(AstNode *node) {
    print(node) ;
    getAstVis()->getOs() << std::endl ;
}


AstVisPrint::~AstVisPrint() {}
