/**
 * \file      AstVisTypeChecking.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Visitor Definition for TypeChecking
 * \details  
 * This file defined an AstVisTypeChecker which is divided into three sub-visitors :
 * AstVisExplore for the prefix treatment :
 * - checks the identifiers nodes are known in the local or global Environment table
   - Raises an exception otherwise
 * AstVisRangeLet for the infix treatment :
   - checks and computes indentifier type of the value introduced by the keyword "let"
   - then maps the pair (identifier, type) in the local Environment table 
   - Raises an exception if the type of the value is wrong
 * AstVisInfer for the postfix treatment :
    - computs and infers programm typing AstNodes Unification
    - Raises an exception if Unification has failed
 * When the "TypeChecker" visit the Ast
    - if an exception has been caught,
    - that means the TypeChecked programm has an incorrect typing 
    - the routine returns TYPECHECKING_FAILURE (1)
 */

#ifndef ASTVISTYPECHECKING_HPP
#define ASTVISTYPECHECKING_HPP

#include "AstVisitor.hpp"
#include "AstVis.hpp"
#include "Type.hpp"
#include "TypeFactory.hpp"
#include <map>
#include <set>

class AstVisPrint;

using std::string ;
using std::pair ;

typedef std::map<string, Type*> EnvironmentMap ;

/* !
 * \class Environment
 * \brief store the local symbols and the global symbols
 */

class Environment {
private:
    std::ostream * os ;
    EnvironmentMap CM ;
    EnvironmentMap GM = {
        {"bool", TypeSimpleFactory(BOOL).create()},
        {"float", TypeSimpleFactory(FLOAT).create()},
        {"int", TypeSimpleFactory(INT).create()},
        {"unit", TypeSimpleFactory(UNIT).create()},
        {"print_newline", TypeFactory({TypeSimpleFactory(UNIT).create(), TypeSimpleFactory(UNIT).create()}).create()},
        {"print_int", TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(UNIT).create()}).create()},
        {"print_float", TypeFactory({TypeSimpleFactory(FLOAT).create(), TypeSimpleFactory(UNIT).create()}).create()},
        {"+",  TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create()}).create()},
        {"-",  TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create()}).create()},
        {"~-", TypeFactory({TypeSimpleFactory(INT).create(), TypeSimpleFactory(INT).create()}).create()}
    } ;
    Type * args ;
public:
    Environment();
    void setOs(std::ostream* os);
    EnvironmentMap getCurrent() const ;
    EnvironmentMap getGlobal() const ;
    Type* getArgs() const;
    void setArgs(Type* args);
    Type * getVarType(string key) ;
    void addVar(string & key, Type * value) ;
    void removeVar(string & key) ;
    void printCurrent() ;
    virtual ~Environment();
};

/* !
 * \class AstVisExplore
 */

class AstVisExplore : public AstVisPrint {
protected:
    Environment * Env ;
    void print(AstNode* node) ;
public:
    AstVisExplore(Environment * Env);
    
    // Node
    
    void visit_node(AstNode* node) override;
    
    // Leaves
    
    void visit_node(AstNodeBool* boolean) override;
    void visit_node(AstNodeFloat* floatingpoint) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeTuple* tuple) override;
    void visit_node(AstNodeUnit* unit) override;
    void visit_node(AstNodeVar* var) override;
    
    // Unary Nodes
    
    void visit_node(AstNodeApp* app) override;
    void visit_node(FunDef *fundef) override;
    void visit_node(AstNodeLetRec *letrec) override;
    void visit_node(AstNodeNeg* neg) override;
    
    // Binary Nodes
    
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeLe *le) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    // Ternary Nodes
    
    void visit_node(AstNodeIf *ite) override;
    
    virtual ~AstVisExplore();
};

typedef std::vector<std::string>::iterator VarIt ;

/* !
 * \class AstVisRangeLet
 */

class AstVisRangeLet : public AstVisExplore {
private:
    void UnificationTuple (VarIt it, TypeComposed **typeMember);
public:
    vector<InitTypeComposed> types ;
    using AstVisExplore::AstVisExplore ;
    void addType(Type *type);
    
    // Node
    
    void visit_node(AstNode* node) override;
    
    // Leaves
    
    void visit_node(AstNodeBool* boolean) override;
    void visit_node(AstNodeFloat* floatingpoint) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeTuple* tuple) override;
    void visit_node(AstNodeUnit* unit) override;
    void visit_node(AstNodeVar* var) override;
    
    // Unary Nodes
    
    void visit_node(AstNodeApp* app) override;
    void visit_node(FunDef *fundef) override;
    void visit_node(AstNodeLetRec *letrec) override;
    void visit_node(AstNodeNeg* neg) override;
    
    // Binary Nodes
    
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeLe *le) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    // Ternary Nodes
    
    void visit_node(AstNodeIf *ite) override;
    
    ~AstVisRangeLet();
};

class AstNodeLeaf ;

/* !
 * \class AstVisInfer
 */

class AstVisInfer : public AstVisPrint {
protected:
    Environment * Env ;
    AstNode * node ;
    Type * type ;
    void InferLeaf (AstNodeLeaf* leaf, Type *type) ;
    void UnificationNode (AstNode *node, Type *type) ;
    void SubstitutePolymorhicTypes(Type * typeApp, Type *type) ;
public:
    AstVisInfer(Environment * Env);
    virtual ~AstVisInfer() ;
    AstNode * getNode() const;
    void setNode(AstNode* node);
    Type* getType() const;
    void setType(Type* type);
    bool isWholeProgramCorrectlyTyped() ;
    void print(Type *type, AstNode* node) ;
    
    // Node
    
    void visit_node(AstNode* node) override;
    
    // Leaves
    
    void visit_node(AstNodeBool* boolean) override;
    void visit_node(AstNodeFloat* floatingpoint) override;
    void visit_node(AstNodeInt* integer) override;
    void visit_node(AstNodeTuple* tuple) override;
    void visit_node(AstNodeUnit* unit) override;
    void visit_node(AstNodeVar* var) override;
    
    // Unary Nodes
    
    void visit_node(AstNodeApp* app) override;
    void visit_node(FunDef *fundef) override;
    void visit_node(AstNodeLetRec *letrec) override;
    void visit_node(AstNodeNeg* neg) override;
    
    // Binary Nodes
    
    void visit_node(AstNodeAdd* add) override;
    void visit_node(AstNodeLe *le) override;
    void visit_node(AstNodeLet* let) override;
    void visit_node(AstNodeLetTuple* lettuple) override;
    void visit_node(AstNodeSub* sub) override;
    
    // Ternary Nodes
    
    void visit_node(AstNodeIf *ite) override;
};

#endif /* ASTVISTYPECHECKING_HPP */

