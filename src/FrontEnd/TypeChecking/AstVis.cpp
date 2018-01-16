#include "AstNode.hpp"
#include "AstNodeLeaf.hpp"
#include "AstNodeUnary.hpp"
#include "AstNodeBinary.hpp"
#include "AstNodeTernary.hpp"
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

// Node

inline void AstVisGhost::visit_node(AstNode* node) {}

// Leaves

inline void AstVisGhost::visit_node(AstNodeBool* boolean) {}
inline void AstVisGhost::visit_node(AstNodeFloat* floatingoint) {}
inline void AstVisGhost::visit_node(AstNodeInt* integer) {}
inline void AstVisGhost::visit_node(AstNodeTuple* tuple) {}
inline void AstVisGhost::visit_node(AstNodeUnit* unit) {}
inline void AstVisGhost::visit_node(AstNodeVar* var) {}

// Unary Nodes

inline void AstVisGhost::visit_node(AstNodeApp* app) {}
inline void AstVisGhost::visit_node(FunDef* fundef) {}
inline void AstVisGhost::visit_node(AstNodeLetRec* letrec) {}
inline void AstVisGhost::visit_node(AstNodeNeg* neg) {}

// BinaryNodes

inline void AstVisGhost::visit_node(AstNodeAdd* add) {}
inline void AstVisGhost::visit_node(AstNodeLet* let) {}
inline void AstVisGhost::visit_node(AstNodeLe* le) {}
inline void AstVisGhost::visit_node(AstNodeLetTuple* lettuple) {}
inline void AstVisGhost::visit_node(AstNodeSub* sub) {}

// Ternary Nodes
    
inline void AstVisGhost::visit_node(AstNodeIf *ite) {} ;


AstVisGhost::~AstVisGhost() {}


// Destructor Visitor

AstVisDestruct::AstVisDestruct() :
AstVisAbstract() {}

// Node

inline void AstVisDestruct::visit_node(AstNode* node) { delete node ; }

// Leaves

inline void AstVisDestruct::visit_node(AstNodeBool* boolean) { delete boolean ; }
inline void AstVisDestruct::visit_node(AstNodeFloat* floatingpoint) { delete floatingpoint ; }
inline void AstVisDestruct::visit_node(AstNodeInt* integer) { delete integer ; }
inline void AstVisDestruct::visit_node(AstNodeTuple* tuple) { delete tuple ; }
inline void AstVisDestruct::visit_node(AstNodeUnit* unit) { delete unit ; }
inline void AstVisDestruct::visit_node(AstNodeVar* var) { delete var ; }

// Unary Nodes

inline void AstVisDestruct::visit_node(AstNodeApp* app) { delete app ; }
inline void AstVisDestruct::visit_node(FunDef* fundef) { delete fundef ; }
inline void AstVisDestruct::visit_node(AstNodeLetRec* letrec) { delete letrec ; }
inline void AstVisDestruct::visit_node(AstNodeNeg* neg) { delete neg ; }

// Binary Nodes

inline void AstVisDestruct::visit_node(AstNodeAdd* add) { delete add ; }
inline void AstVisDestruct::visit_node(AstNodeLe* le) { delete le ; }
inline void AstVisDestruct::visit_node(AstNodeLet* let) { delete let ; }
inline void AstVisDestruct::visit_node(AstNodeLetTuple* lettuple) { delete lettuple ; }
inline void AstVisDestruct::visit_node(AstNodeSub* sub) { delete sub ; }

// Ternary Nodes
    
inline void AstVisDestruct::visit_node(AstNodeIf *ite) { delete ite ; }

AstVisDestruct::~AstVisDestruct() {}

// Printer Visitor

AstVisPrint::AstVisPrint() :
AstVisAbstract() {}

// Node

void AstVisPrint::visit_node(AstNode * node) {
    print_node_then_new_line(node) ;
}

// Leaves

void AstVisPrint::visit_node(AstNodeBool* boolean) {
    print_node_then_new_line(boolean) ;
}
void AstVisPrint::visit_node(AstNodeFloat* floatingpoint) {
    print_node_then_new_line(floatingpoint) ;
}
void AstVisPrint::visit_node(AstNodeInt* integer) {
    print_node_then_new_line(integer) ;
}
void AstVisPrint::visit_node(AstNodeTuple* tuple) {
    print_node_then_new_line(tuple) ;
}
void AstVisPrint::visit_node(AstNodeUnit* unit) {
    print_node_then_new_line(unit) ;
}
void AstVisPrint::visit_node(AstNodeVar* var) {
    print_node_then_new_line(var) ;
}

// Unary Nodes

void AstVisPrint::visit_node(AstNodeApp* app) {
    print_node_then_new_line(app) ;
}
void AstVisPrint::visit_node(FunDef* fundef) {
    print_node_then_new_line(fundef) ;
}
void AstVisPrint::visit_node(AstNodeLetRec * letrec) {
    print_node_then_new_line(letrec) ;
}
void AstVisPrint::visit_node(AstNodeNeg* neg) {
    print_node_then_new_line(neg) ;
}

// Binary Nodes

void AstVisPrint::visit_node(AstNodeAdd* add) {
    print_node_then_new_line(add) ;
}
void AstVisPrint::visit_node(AstNodeLe* le) {
    print_node_then_new_line(le) ;
}
void AstVisPrint::visit_node(AstNodeLet* let) {
    print_node_then_new_line(let) ;
}
void AstVisPrint::visit_node(AstNodeLetTuple* lettuple) {
    print_node_then_new_line(lettuple) ;
}
void AstVisPrint::visit_node(AstNodeSub* sub) {
    print_node_then_new_line(sub) ;
}

// Ternary Nodes

void AstVisPrint::visit_node(AstNodeIf* ite) {
    print_node_then_new_line(ite) ;
}

void AstVisPrint::print(AstNode * node) {
    printIndent() ;
    getAstVis()->getOs() << node->class_code_to_string() + " " << *node ;
}

void AstVisPrint::print_node_then_new_line(AstNode *node) {
    print(node) ;
    getAstVis()->getOs() << std::endl ;
}

void AstVisPrint::printIndent() {
    for (int i = 0 ; i < getAstVis()->getIndent() ; i++) {
        getAstVis()->getOs() << getAstVis()->INDENT ;
    }
}


AstVisPrint::~AstVisPrint() {}
