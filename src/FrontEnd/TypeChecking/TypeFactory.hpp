#ifndef TYPEFACTORY_HPP
#define TYPEFACTORY_HPP

#include "Type.hpp"
#include <vector>

using std::vector;

class InitTypeComposed {
public:
    InitTypeComposed(typeComposed t, typeSimple ts);
    InitTypeComposed(typeComposed t, TypeComposed *tc);
    typeComposed GetType() const;
    typeSimple GetTypeSimple() const;
    TypeComposed * GetTypeComposed() const;
    virtual ~InitTypeComposed();
private:
    typeComposed t ;
    union {
        typeSimple ts ;
        TypeComposed *tc ;
    } ;
};

class TypeComposedFactory {
public:
    TypeComposedFactory(std::initializer_list<InitTypeComposed>);
    virtual TypeComposed * create() = 0 ;
    virtual ~TypeComposedFactory() = 0 ;
protected:
    vector<InitTypeComposed> types ;
};

class TypeTupleFactory : public TypeComposedFactory {
public:
    using TypeComposedFactory::TypeComposedFactory ;
    TypeTuple * create() override;
    ~TypeTupleFactory();
private:
    void cons(TypeTuple **typeTuple, unsigned i) ;
};

class TypeAppFactory : public TypeComposedFactory {
public:
    using TypeComposedFactory::TypeComposedFactory ;
    TypeApp * create() override;
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
};

class TypeFactory {
public:    
    TypeFactory(std::initializer_list<Type *> types);
    Type * create() ;
    ~TypeFactory();
private:
    vector<Type *> types ;
};

#endif /* TYPEFACTORY_HPP */

