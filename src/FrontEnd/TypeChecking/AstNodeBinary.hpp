/**
 * \file      AstNodeBinary.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of Ast binary node
 *
 */

#ifndef AST_NODE_BINARY_H
#define AST_NODE_BINARY_H

#include "AstNodeLeaf.hpp"

class AstNode ;
class FunDef ;

/* ! 
 * \class AstNodeBinary
 * \brief Abstract Class for Ast binary nodes definition
 */

class AstNodeBinary : public AstNode {
protected:
    AstNode * t1, * t2 ; /* ! < left child t1, right child t2 */
public:
    /* !
     * \brief Constructor
     * \params int class_code, AstNode *t1, AstNode *t2
     */
    AstNodeBinary(int class_code, AstNode *t1, AstNode *t2);
    /* !
     * \brief Getter of t1
     * \return AstNode *t1
     */
    AstNode* getT1() const;
    /* !
     * \brief Getter of t2
     * \return AstNode* t2
     */
    AstNode* getT2() const;
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeBinary() = 0 ;
};

/* ! 
 * \class InfixOperator
 * \brief Abstract Class for infix operators definition
 */

class InfixOperator : public AstNodeBinary {
public:
    using AstNodeBinary::AstNodeBinary ;
    virtual ~InfixOperator() = 0 ;

};

/* ! 
 * \class AstNodeAdd
 * \brief "+" infix operator node
 */

class AstNodeAdd : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeAdd(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeAdd();
};

class AstNodeArray : public AstNodeBinary {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeArray(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeArray();
};

/* ! 
 * \class AstNodeEq
 * \brief "=" infix operator node
 */

class AstNodeEq : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeEq(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeEq();
};

/* ! 
 * \class AstNodeFadd
 * \brief "+." infix operator node
 */

class AstNodeFadd : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeFadd(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFadd();
};

/* ! 
 * \class AstNodeFdiv
 * \brief "/." infix operator node
 */

class AstNodeFdiv : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeFdiv(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFdiv();
};

/* ! 
 * \class AstNodeFmul
 * \brief "*." infix operator node
 */

class AstNodeFmul : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeFmul(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFmul();
};

/* ! 
 * \class AstNodeFsub
 * \brief "-." infix operator node
 */

class AstNodeFsub : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeFsub(AstNode * t1, AstNode * t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFsub();
};

/* ! 
 * \class AstNodeGet
 * \brief ".(<index>)" operator to get an element from an array
 */

class AstNodeGet : public AstNodeBinary {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeGet(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeGet();
};

/* ! 
 * \class AstNodeLe
 * \brief "<=" infix operator node
 */

class AstNodeLe : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeLe(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLe();
};

/* ! 
 * \class AstNodeLetRec
 * \brief Ast let node for values definition
 */

class AstNodeLet : public AstNodeBinary {
    AstNodeVar var ; /*!< identifier of the value */
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2, string var_name
     */
    AstNodeLet(AstNode *t1, AstNode *t2, std::string var_name);
    /* !
     * \brief Getter of var
     * \return AstNodeVar var
     */
    AstNodeVar getVar() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLet();
};

/* ! 
 * \class AstNodeLetRec
 * \brief Ast let node for tuples definition
 */

class AstNodeLetTuple : public AstNodeBinary {
protected:
    std::vector<std::string> var_list ; /*!< identifier of the values of the tuple  */
public:
    /* !
     * \brief Constructor
     * \params vector<string> var_list, AstNode *t1, AstNode *t2
     */
    AstNodeLetTuple(std::vector<std::string> var_list, AstNode *t1, AstNode *t2);
    /* !
     * \brief Getter of var_list
     * \return vector<string> var_list
     */
    std::vector<std::string> & getVar_list() ;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLetTuple();
};

/* ! 
 * \class AstNodeSub
 * \brief "-" infix operator node
 */

class AstNodeSub : public InfixOperator {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1, AstNode *t2
     */
    AstNodeSub(AstNode *t1, AstNode *t2);
    void accept(AstVisAbstract* vis) override;
    ~AstNodeSub();
};

#endif
