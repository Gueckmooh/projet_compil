/**
 * \file      Type.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Typing Definition for TypeChecking
 * \details
 * The definition of a basic type is the following :
 * type TypeSimple = Bool | Int | Float | Unit | Poly of char
 * The definition of a recursive Composed type is the following :
 * type TypeComposed = Simple of TypeSimple | Tuple of TypeComposed | Application of TypeComposed | Next of TypeSimple * TypeComposed
 * Finally, a type is defined recursively as follows :
 * type Type = Simple of TypeSimple | Composed of typeComposed | Next of Type
 * Also, basic types can be polymorphic when a function definition is introduced
 * and its polymorphic type(s) is(are) mapped into the Polymorphic Types Map
 * The Polymorphic Types Map enables to associate each introduced polymorphic type
 * to a true basic type when unification of types is processed
 */

#ifndef TYPECOMPOSED_HPP
#define	TYPECOMPOSED_HPP

#include "print_ast.h"
#include <ostream>
#include <map>

/* !
 * \namespace Types
 * \brief Enum types to define basic types : BOOL, INT, FLOAT, UNIT, POLY
 *        Enum types to define composed types : Simple, Tuple, Application
 */

namespace Types {
    enum typeSimple {BOOL, INT, FLOAT, UNIT, POLY} ;
    enum typeComposed {Simple, Tuple, Application} ;
}

using namespace Types ;
class Type;
typedef std::map<char, Type*> PolyMap ; /* ! < Map of defined Polymorphic Types */

/* !
 * \class TypeSimple
 * \brief basic type definition
 */

class TypeSimple {
public:
    TypeSimple(typeSimple ts);
    TypeSimple(typeSimple ts, char poly);
    TypeSimple(TypeSimple *typeSimple);
    typeSimple getType() const;
    char getPoly() const;
    static char getNextPoly();
    static void resetNextPoly();
    static Type * getMappedPoly(char poly);
    static void mapPoly(char poly, Type * type);
    static void substitutePoly(Type** substitued, Type* substitution);
    static void printPoly();
    static void resetPoly () ;
    static std::ostream & getOs();
    static void setOs (std::ostream * os);
    bool isCorrectlyTyped (TypeSimple *typeSimple) ;
    static TypeSimple * copyTypeSimple(TypeSimple *typeSimple);
    friend std::ostream& operator<<(std::ostream& os, TypeSimple& ts) ;
    virtual ~TypeSimple();
protected:
    typeSimple ts ;
    char poly ;
    static std::ostream * os ;
    static char next_poly ;
    static PolyMap PM ;
};

class TypeTuple;
class TypeApp;
class AstVisInfer;

/* !
 * \class TypeComposed
 * \brief composed type definition
 */

class TypeComposed {
public:
    TypeComposed(TypeSimple *ts) ;
    TypeComposed(TypeSimple *ts, unsigned l) ;
    TypeComposed(TypeSimple *ts, TypeComposed *tc) ;
    TypeComposed(TypeTuple  *tt) ;
    TypeComposed(TypeTuple  *tt, TypeComposed *tc) ;
    TypeComposed(TypeApp *ta) ;
    TypeComposed(TypeApp    *ta, TypeComposed *tc) ;
    unsigned size() const;
    typeComposed getType() const;
    TypeApp* getApp() const;
    TypeComposed* getNext() const;
    void setNext(TypeComposed* tc);
    TypeSimple* getSimple() const;
    TypeTuple* getTuple() const;
    bool isPoly();
    bool isCorrectlyTyped (TypeComposed *typeComposed) ;
    virtual void print(std::ostream& os, TypeComposed& typeComposed) = 0 ;
    static void deleteType (TypeComposed *typeComposed) ;
    virtual ~TypeComposed() = 0 ;
protected:
    unsigned l ;
    typeComposed t ;
    TypeSimple   *ts ;
    TypeTuple    *tt ;
    TypeApp      *ta ;
    TypeComposed *tc ;
    bool areCorrectlyTyped (TypeComposed *typeComposed);
};

/* !
 * \class TypeTuple
 * \brief tuple type definition
 */

class TypeTuple : public TypeComposed {
public:
    using TypeComposed::TypeComposed ;
    void print(std::ostream& os, TypeComposed& typeComposed) override;
    static TypeTuple * copyTypeTuple(TypeTuple* typeTuple);
    friend std::ostream& operator<<(std::ostream& os, TypeTuple& typeTuple) ;
    ~TypeTuple() ;
};

/* !
 * \class TypeApp
 * \brief application type definition
 */

class TypeApp : public TypeComposed {
public:
    using TypeComposed::TypeComposed ;
    void print(std::ostream& os, TypeComposed& typeComposed) override;
    static TypeApp* copyTypeApp(TypeApp* typeApp);
    friend std::ostream& operator<<(std::ostream& os, TypeApp& typeApp) ;
    ~TypeApp();
};

/* !
 * \class Type
 * \brief Type definition
 */

class Type {
public:
    Type(TypeSimple *ts);
    Type(TypeTuple  *tt);
    Type(TypeApp    *ta);
    Type(TypeComposed *tc);
    typeComposed GetType() const;
    void SetType(typeComposed t);
    TypeSimple* GetTypeSimple() const;
    void SetTypeSimple(TypeSimple* ts);
    TypeComposed* GetTypeComposed() const;
    void SetTypeComposed(TypeComposed *tc);
    Type* getNext() const;
    void setNext(Type* next);
    bool isPoly();
    bool isCorrectlyTyped (Type *type) ;
    static Type* Unification (Type *typeApp, Type *typeArgs) ;
    void printApplication(std::ostream& os, Type& type);
    friend std::ostream& operator<<(std::ostream& os, Type& type);
    static Type* copyType(Type* orig) ;
    static Type* copyTypeRec(Type* orig) ;
    static void deleteType(Type *type);
    static void deleteTypeRec(Type* type);
    ~Type();
private:
    typeComposed t ;
    union {
        TypeSimple   *ts ;
        TypeComposed *tc ;
    };
    Type *next ;
};

#endif	/* TYPECOMPOSED_HPP */

