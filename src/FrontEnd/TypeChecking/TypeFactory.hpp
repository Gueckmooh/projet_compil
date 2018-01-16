#ifndef TYPEFACTORY_HPP
#define TYPEFACTORY_HPP

#include "Type.hpp"
#include <vector>
#include <string>

using std::vector;

class Environment;

class InitTypeComposed {
public:
    InitTypeComposed(typeComposed t, typeSimple ts);
    InitTypeComposed(typeComposed t, typeSimple ts, char poly);
    InitTypeComposed(typeComposed t, TypeComposed *tc);
    typeComposed GetType() const;
    typeSimple GetTypeSimple() const;
    char GetPoly() const;
    TypeComposed * GetTypeComposed() const;
    virtual ~InitTypeComposed();
private:
    typeComposed t ;
    char poly ;
    union {
        typeSimple ts ;
        TypeComposed *tc ;
    } ;
};

class TypeComposedFactory {
public:
    TypeComposedFactory(std::initializer_list<InitTypeComposed>);
    TypeComposedFactory(vector<InitTypeComposed> types);
    virtual TypeComposed * create() = 0 ;
    virtual ~TypeComposedFactory() = 0 ;
protected:
    vector<InitTypeComposed> types ;
};

class TypeTupleFactory : public TypeComposedFactory {
public:
    using TypeComposedFactory::TypeComposedFactory ;
    TypeTuple * create() override;
    static TypeTuple * createPoly(vector<std::string> vars, char poly, Environment *Env);
    TypeTuple * createReversal() ;
    ~TypeTupleFactory();
private:
    void cons(TypeTuple **typeTuple, unsigned i) ;
};

class FunDef;
class Environment;

class TypeAppFactory : public TypeComposedFactory {
public:
    using TypeComposedFactory::TypeComposedFactory ;
    TypeApp * create() override;
    static void createPoly(FunDef *fundef, Environment *Env);
    ~TypeAppFactory();
private:
    void cons(TypeApp **typeApp, unsigned i) ;
};

class TypeSimpleFactory {
public:
    TypeSimpleFactory(typeSimple ts);
    Type * create() ;
    ~TypeSimpleFactory();
protected:
    typeSimple ts ;
    char poly = 'a' ;
};

class TypeFactory {
public:
    TypeFactory(std::initializer_list<Type *> types);
    TypeFactory(vector<Type*> types);
    Type * create() ;
    static Type* createPoly(unsigned size);
    ~TypeFactory();
private:
    vector<Type *> types ;
};

#endif /* TYPEFACTORY_HPP */

