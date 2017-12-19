#ifndef AST_NODE_TERNARY_H
#define AST_NODE_TERNARY_H

class AstNode ;

class AstNodeTernary : public virtual AstNode {
protected:
    AstNode *t1, *t2, *t3 ;
public:
    AstNodeTernary(AstNode *t1, AstNode *t2, AstNode *t3);
    void traversal(AstVisitor& vis) override;
    virtual ~AstNodeTernary() = 0 ;
};

class AstNodeIf : public AstNodeTernary {
public:
    AstNodeIf(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodeIf();
};

class AstNodePut : public AstNodeTernary {
public:
    AstNodePut(AstNode *t1, AstNode *t2, AstNode *t3);
    ~AstNodePut();
};

#endif
