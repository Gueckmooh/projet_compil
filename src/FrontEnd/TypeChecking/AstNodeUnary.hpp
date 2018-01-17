/**
 * \file      AstNodeUnary.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of Ast unary node
 *
 */

#ifndef AST_NODE_UNARY_H
#define AST_NODE_UNARY_H

#include "AstNodeLeaf.hpp"

class AstNode ;

/* ! 
 * \class AstNodeUnary
 * \brief Abstract Class for Ast unary nodes definition
 */

class AstNodeUnary : public AstNode {
protected:
   AstNode * t1 ; /* ! < child t1 */
public:
    /* !
     * \brief Constructor
     * \params int class_code, AstNode *t1
     */
    AstNodeUnary(int class_code, AstNode * t1);
    /* !
     * \brief Getter of ct1
     * \return AstNode *t1
     */
    AstNode* getT1() const;
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeUnary() = 0 ;
};

/* ! 
 * \class AstNodeApp
 * \brief Ast application node
 */

class AstNodeApp : public AstNodeTuple {
protected :
    AstNodeVar *var ; /*!<identifier of application name */
public:
    /* !
     * \brief Constructor
     * \params int class_code, AstNode *t1
     */
    AstNodeApp(std::vector<AstNode *> args_list,AstNodeVar *var) ;
    /* !
     * \brief Getter of var
     * \return string var
     */
    AstNodeVar* getVar() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeApp() ;
};

/* ! 
 * \class AstNodeFneg
 * \brief Ast floating point negation node
 */

class AstNodeFneg : public AstNodeUnary {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1
     */
    AstNodeFneg(AstNode *t1) ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFneg() ;
};

/* ! 
 * \class AstNodeNeg
 * \brief Ast integer negation node
 */

class AstNodeNeg : public AstNodeUnary {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1
     */
    AstNodeNeg(AstNode *t1) ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeNeg() ;
};

/* ! 
 * \class AstNodeNot
 * \brief Ast boolean negation node
 */

class AstNodeNot : public AstNodeUnary {
public:
    /* !
     * \brief Constructor
     * \params AstNode *t1
     */
    AstNodeNot(AstNode *t1) ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeNot() ;
};

/* ! 
 * \class AstNodeFundef
 * \brief Ast function definition node
 */

class FunDef : public AstNodeUnary {
protected:
    AstNodeVar var ; /* ! < identifier function */
    std::vector<std::string> args_list ; /* ! < arguments list of function */
public:
    /* !
     * \brief Constructor
     * \params string var_name, vector<string> args_list, AstNode* body
     */
    FunDef(std::string var_name, std::vector<std::string> args_list, AstNode *body);
    AstNodeVar & getVar();
    std::vector<std::string> & getArgs();
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    void traversal(AstVisitor* vis) override;
    ~FunDef();
};

/* ! 
 * \class AstNodeLetRec
 * \brief Ast let rec node
 */

class AstNodeLetRec : public AstNodeUnary {
    FunDef * fun_def ; /* ! < definition of funtion introduved by let rec */
public:
    /* !
     * \brief Constructor
     * \params FunDef* fundef, AstNode *t1
     */
    AstNodeLetRec(FunDef *fun_def, AstNode *t1);
    /* !
     * \brief Getter of function definition
     * \return FunDef *
     */
    FunDef* getFunDef() const;
    void traversal(AstVisitor* vis) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeLetRec();
};


#endif
