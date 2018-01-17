/**
 * \file      Type.cpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Type Factory for TypeChecking
 *
 */

#include "TypeFactory.hpp"
#include "AstVisTypeChecking.hpp"
#include "AstNodeUnary.hpp"
#include <cassert>

InitTypeComposed::InitTypeComposed(typeComposed t, typeSimple ts) :
t(t), poly(TypeSimple::getNextPoly()), ts(ts) {}

InitTypeComposed::InitTypeComposed(typeComposed t, typeSimple ts, char poly) :
t(t), poly(poly), ts(ts) {}

InitTypeComposed::InitTypeComposed(typeComposed t, TypeComposed* tc) :
t(t), poly(TypeSimple::getNextPoly()), tc(tc) {}

typeComposed InitTypeComposed::GetType() const {
    return t;
}

typeSimple InitTypeComposed::GetTypeSimple() const {
    return ts;
}

char InitTypeComposed::GetPoly() const {
    return poly ;
}


TypeComposed* InitTypeComposed::GetTypeComposed() const {
    return tc;
}


InitTypeComposed::~InitTypeComposed() {}


TypeComposedFactory::TypeComposedFactory(std::initializer_list<InitTypeComposed> types) :
types(types) {}
TypeComposedFactory::TypeComposedFactory(vector<InitTypeComposed> types) :
types(types) {}
TypeComposedFactory::~TypeComposedFactory() {}

void TypeTupleFactory::cons(TypeTuple **typeTuple, unsigned i) {
    if (i == types.size() - 1) {
        switch(types[i].GetType()) {
            case Simple :
                *typeTuple = new TypeTuple(new TypeSimple(types[i].GetTypeSimple(), types[i].GetPoly())) ;
                break ;
            case Tuple :
                *typeTuple = new TypeTuple((TypeTuple *)types[i].GetTypeComposed()) ;
                break ;
            case Application :
                *typeTuple = new TypeTuple((TypeApp *)types[i].GetTypeComposed()) ;
                break ;
            assert(false) ;
        }
        return ;
    }
    cons(typeTuple, i + 1) ;
    switch(types[i].GetType()) {
        case Simple :
            *typeTuple = new TypeTuple(new TypeSimple(types[i].GetTypeSimple(), types[i].GetPoly()), *typeTuple) ;
            break ;
        case Tuple :
            *typeTuple = new TypeTuple((TypeTuple *)types[i].GetTypeComposed(), *typeTuple) ;
            break ;
        case Application :
            *typeTuple = new TypeTuple((TypeApp *)types[i].GetTypeComposed(), *typeTuple) ;
            break ;
        assert(false) ;
    }
}

TypeTuple * TypeTupleFactory::create() {
    TypeTuple *typeTuple = NULL ;
    cons(&typeTuple, 0) ;
    return typeTuple ;
}

TypeTuple * TypeTupleFactory::createPoly(vector<string> vars, char poly, Environment *Env) {
    unsigned i = 0 ;
    TypeTuple * tuple = new TypeTuple(new TypeSimple(POLY, poly++), vars.size() - i) ;
    Env->addVar(vars[i++], new Type(TypeSimple::copyTypeSimple(tuple->getSimple()))) ;
    TypeTuple * AC = tuple ;
    while (i < vars.size()) {
        AC->setNext(new TypeTuple(new TypeSimple(POLY, poly++), vars.size() - i)) ;
        AC = (TypeTuple*)AC->getNext() ;
        Env->addVar(vars[i++], new Type(TypeSimple::copyTypeSimple(AC->getSimple()))) ;
    }
    return tuple ;
}

TypeTuple* TypeTupleFactory::createReversal() {
    TypeTuple * tuple = NULL ; 
    unsigned i = 0 ;
    switch(types[i].GetType()) {
        case Simple :
            tuple = new TypeTuple(new TypeSimple(types[i].GetTypeSimple()), types.size()) ;
            break ;
        case Tuple :
            tuple = new TypeTuple((TypeTuple *)types[i].GetTypeComposed()) ;
            break ;
        case Application :
            tuple = new TypeTuple((TypeApp *)types[i].GetTypeComposed()) ;
            break ;
        assert(false) ;
    }
    TypeTuple * AC = tuple ;
    i++ ;
    for(; i < types.size() ; i++) {
        switch(types[i].GetType()) {
            case Simple :
                AC->setNext(new TypeTuple(new TypeSimple(types[i].GetTypeSimple()), types.size() - i)) ;
                break ;
            case Tuple :
                AC->setNext(new TypeTuple((TypeTuple *)types[i].GetTypeComposed())) ;
                break ;
            case Application :
                AC->setNext(new TypeTuple((TypeApp *)types[i].GetTypeComposed())) ;
                break ;
            assert(false) ;
        }
        AC = (TypeTuple*)AC->getNext() ;
    }
     return tuple ;
}


TypeTupleFactory::~TypeTupleFactory() {}

void TypeAppFactory::cons(TypeApp** typeApp, unsigned i) {
    if (i == types.size() - 1) {
        switch(types[i].GetType()) {
            case Simple :
                *typeApp = new TypeApp(new TypeSimple(types[i].GetTypeSimple())) ;
                break ;
            case Tuple :
                *typeApp = new TypeApp((TypeTuple *)types[i].GetTypeComposed()) ;
                break ;
            default :
                assert(false) ;
        }
        return ;
    }
    cons(typeApp, i + 1) ;
    switch(types[i].GetType()) {
        case Simple :
            *typeApp = new TypeApp(new TypeSimple(types[i].GetTypeSimple()), *typeApp) ;
            break ;
        case Tuple :
            *typeApp = new TypeApp((TypeTuple *)types[i].GetTypeComposed(), *typeApp) ;
            break ;
        case Application :
            *typeApp = new TypeApp((TypeApp *)types[i].GetTypeComposed(), *typeApp) ;
            break ;
    }
}

TypeApp * TypeAppFactory::create() {
    TypeApp *typeApp = NULL ;
    cons(&typeApp, 0) ;
    return typeApp ;
}

void TypeAppFactory::createPoly(FunDef *fundef, Environment *Env) {
    vector<string> args = fundef->getArgs() ;
    unsigned i = 0 ;
    TypeApp * app = new TypeApp(new TypeSimple(POLY)) ;
    Env->addVar(args[i++], new Type(TypeSimple::copyTypeSimple(app->getSimple()))) ;
    TypeApp * AC = app ;
    while (i <= fundef->getArgs().size() - 1) {
        AC->setNext(new TypeApp(new TypeSimple(POLY))) ;
        AC = (TypeApp*)AC->getNext() ;
        Env->addVar(args[i++], new Type(TypeSimple::copyTypeSimple(AC->getSimple()))) ;
        i++ ;
    }
    AC->setNext(new TypeApp(new TypeSimple(POLY))) ;
    Env->addVar(fundef->getVar().getVar_name(), new Type(app)) ;
}


TypeAppFactory::~TypeAppFactory() {}

TypeSimpleFactory::TypeSimpleFactory(typeSimple ts) :
ts(ts) {}

Type * TypeSimpleFactory::create() {
    return new Type(new TypeSimple(ts)) ;
}

TypeSimpleFactory::~TypeSimpleFactory() {}

TypeFactory::TypeFactory(std::initializer_list<Type*> types) :
types(types) {
    if(types.size() < 2)
        assert(false) ;
}

TypeFactory::TypeFactory(vector<Type*> types) :
types(types) {
    if(types.size() < 2)
        assert(false) ;
}

Type* TypeFactory::create() {
    for(unsigned i = 0 ; i < types.size() - 1 ; i++)
        types[i]->setNext(types[i+1]) ;
    return types.front() ;
}

Type * TypeFactory::createPoly(unsigned size) {
    unsigned i = 0 ;
    Type * app = TypeSimpleFactory(POLY).create() ;
    Type * AC = app ;
    i++ ;
    while (i < size - 1) {
        AC->setNext(TypeSimpleFactory(POLY).create()) ;
        AC = AC->getNext() ;
        i++ ;
    }
    AC->setNext(TypeSimpleFactory(POLY).create()) ;
    return app ;
}

TypeFactory::~TypeFactory() {}
