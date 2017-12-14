
#ifndef AST_LET_REC_NODE_H
#define AST_LET_REC_NODE_H

#include "AstNode.hpp"
#include "FunDef.hpp"

class AstNodeLetRec  :public AstNode {
protected:
    FunDef *fun_def;
    AstNode *t1;
public:
    AstNodeLetRec(FunDef *fun_def, AstNode *t1);
    ~AstNodeLetRec();

    bool infer_types();
    void print();
};

#endif
