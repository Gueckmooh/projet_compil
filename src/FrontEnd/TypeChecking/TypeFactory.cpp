#include "TypeFactory.hpp"
#include <cassert>

InitTypeComposed::InitTypeComposed(typeComposed t, typeSimple ts) :
t(t), ts(ts) {}

InitTypeComposed::InitTypeComposed(typeComposed t, TypeComposed* tc) :
t(t), tc(tc) {}

typeComposed InitTypeComposed::GetType() const {
    return t;
}

typeSimple InitTypeComposed::GetTypeSimple() const {
    return ts;
}

TypeComposed* InitTypeComposed::GetTypeComposed() const {
    return tc;
}


InitTypeComposed::~InitTypeComposed() {}


TypeComposedFactory::TypeComposedFactory(std::initializer_list<InitTypeComposed> types) :
types(types) {}

TypeComposedFactory::~TypeComposedFactory() {}

void TypeTupleFactory::cons(TypeTuple **typeTuple, unsigned i) {
    if (i == types.size() - 1) {
        switch(types[i].GetType()) {
            case Simple :
                *typeTuple = new TypeTuple(new TypeSimple(types[i].GetTypeSimple())) ;
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
            *typeTuple = new TypeTuple(new TypeSimple(types[i].GetTypeSimple()), *typeTuple) ;
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
        assert(false) ;
    }
}

TypeApp * TypeAppFactory::create() {
    TypeApp *typeApp = NULL ;
    cons(&typeApp, 0) ;
    return typeApp ;
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

Type* TypeFactory::create() {
    for(unsigned i = 0 ; i < types.size() - 1 ; i++)
        types[i]->setNext(types[i+1]) ;
    return types.front() ;
}

TypeFactory::~TypeFactory() {}
