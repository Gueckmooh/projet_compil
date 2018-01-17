/**
 * \file      AstNodeLeaf.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of Ast leaf
 *
 */

#ifndef AST_NODE_LEAF_H
#define AST_NODE_LEAF_H

#include "AstNode.hpp"
#include "AstVisitor.hpp"
#include "AstVis.hpp"
#include <vector>
#include <string>

class AstVisAbstract;
class AstNode ;

/* ! 
 * \class AstNodeLeaf
 * \brief Abstract Class for Ast leaves definition
 */

class AstNodeLeaf : public AstNode {
public:
    /* !
     * \brief Constructor
     * \params int class_code
     */
    AstNodeLeaf(int class_code) ;
    void traversal(AstVisitor* vis) override;
    virtual ~AstNodeLeaf() = 0 ;
};

/* ! 
 * \class AstNodeBool
 * \brief boolean node
 */

class AstNodeBool : public AstNodeLeaf {
protected:
    bool b; /*!< value of boolean */
public:
    /* !
     * \brief Constructor
     * \params bool b
     */
    AstNodeBool(bool b) ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeBool() ;
};

/* ! 
 * \class AstNodeFloat
 * \brief floating point node
 */

class AstNodeFloat : public AstNodeLeaf {
protected:
    float f; /*!< value of floating point */
public:
    /* !
     * \brief Constructor
     * \params float f
     */
    AstNodeFloat(float f) ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeFloat() ;
};

/* ! 
 * \class AstNodeInt
 * \brief integer node
 */

class AstNodeInt : public AstNodeLeaf {
protected:
    int i; /*!< value of integer */
public:
    /* !
     * \brief Constructor
     * \params integer i
     */
    AstNodeInt(int i) ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeInt() ;
};

/* ! 
 * \class AstNodeTuple
 * \brief tuple node
 */

class AstNodeTuple : public AstNodeLeaf {
protected:
    std::vector<AstNode *> var_list; /*!< nodes list of tuple */
public:
    /* !
     * \brief Constructor
     * \params vector <AstNode*>
     */
    AstNodeTuple(std::vector<AstNode *> var_list) ;
    /* !
     * \brief Getter of nodes list of tuple
     * \return vector <AstNode*> nodes list of tuple
     */
    std::vector<AstNode*> getVar_list() const;
    void traversal(AstVisitor* vis) override;
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeTuple() ;
};

/* ! 
 * \class AstNodeUnit
 * \brief unit node
 */

class AstNodeUnit : public AstNodeLeaf {
public:
    /* !
     * \brief Constructor
     */
    AstNodeUnit();
    std::ostream& print(std::ostream& os) override;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeUnit() ;
};

/* ! 
 * \class AstNodeVar
 * \brief identifier node
 */

class AstNodeVar : public AstNodeLeaf {
protected:
    std::string var_name ; /*!< identifier */
public:
    /* !
     * \brief Constructor
     * \params string var_name
     */
    AstNodeVar(std::string var_name) ;
    /* !
     * \brief Getter of var_name
     * \return string var_name
     */
    std::string & getVar_name() ;
    std::ostream& print(std::ostream& os) override ;
    void accept(AstVisAbstract* vis) override;
    ~AstNodeVar() ;
};

#endif
