#ifndef TYPECOMPOSED_HPP
#define	TYPECOMPOSED_HPP

#include "print_ast.h"
#include <ostream>

namespace Types {
    enum typeSimple {BOOL, INT, FLOAT, UNIT} ;
    enum typeComposed {Simple, Tuple, Application} ;
}

using namespace Types ;

class TypeSimple {
public:
    TypeSimple(typeSimple ts);
    typeSimple getType() const;
    bool isCorrectlyTyped (TypeSimple *typeSimple) ;
    friend std::ostream& operator<<(std::ostream& os, TypeSimple& ts) ;
    virtual ~TypeSimple();
protected:
    typeSimple ts ;
};

class TypeTuple;
class TypeApp;
class AstVisInfer;

class TypeComposed {
public:
    TypeComposed();
    TypeComposed(TypeSimple *ts) ;
    TypeComposed(TypeSimple *ts, TypeComposed *tc) ;
    TypeComposed(TypeTuple  *tt) ;
    TypeComposed(TypeTuple  *tt, TypeComposed *tc) ;
    TypeComposed(TypeApp *ta) ;
    TypeComposed(TypeApp    *ta, TypeComposed *tc) ;
    bool isCorrectlyTyped (TypeComposed *typeComposed) ;
    virtual void print(std::ostream& os, TypeComposed& typeComposed) = 0 ;
    //static void copyTypeComposed(TypeComposed* copy, TypeComposed* orig) ;
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

class TypeTuple : public TypeComposed {
public:
    using TypeComposed::TypeComposed ;
    void print(std::ostream& os, TypeComposed& typeComposed) override;
    friend std::ostream& operator<<(std::ostream& os, TypeTuple& typeTuple) ;
    ~TypeTuple() ;
};

class TypeApp : public TypeComposed {
public:
    using TypeComposed::TypeComposed ;
    void print(std::ostream& os, TypeComposed& typeComposed) override;
    friend std::ostream& operator<<(std::ostream& os, TypeApp& typeApp) ;
    ~TypeApp();
};

class Type {
public:
    Type(TypeSimple *ts);
    Type(TypeTuple  *tt);
    Type(TypeApp    *ta);
    Type(Type * orig);
    typeComposed GetType() const;
    TypeSimple* GetTypeSimple() const;
    Type* getNext() const;
    void setNext(Type* next);
    static Type* Unification (Type *type1, Type *type2, AstVisInfer & infer) ;
    friend std::ostream& operator<<(std::ostream& os, const Type& type);
    static void deleteLink(Type *type);
    static void deleteType(Type *type);
    static void deleteTypeRec(Type* type, Type* fin);
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

