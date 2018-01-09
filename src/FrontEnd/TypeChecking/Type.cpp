#include "Type.hpp"
#include "TypeFactory.hpp"
#include "AstVisTypeChecking.hpp"
#include <cassert>
#include <set>

TypeSimple::TypeSimple(typeSimple ts) :
ts(ts) {}

typeSimple TypeSimple::getType() const {
    return ts;
}

bool TypeSimple::isCorrectlyTyped(TypeSimple *typeSimple) {
    return ts == typeSimple->ts ;
}

std::ostream& operator<<(std::ostream& os, TypeSimple& typeSimple) {
    std::string type_str ;
    switch(typeSimple.ts) {
	case BOOL :
	    type_str = "bool";
	    break ;
	case FLOAT :
	    type_str = "float";
	    break ;
	case INT :
	    type_str = "int";
	    break ;
	case UNIT :
	    type_str = "unit" ;
            break ;
        assert(false) ;
        
    }
    return os << type_str ;
}

TypeSimple::~TypeSimple() {}

TypeComposed::TypeComposed(TypeSimple *ts) :
l(1), t(Simple), ts(ts), tt(NULL), ta(NULL), tc(NULL)  {}

TypeComposed::TypeComposed(TypeSimple *ts, TypeComposed *tc) :
l(1 + tc->l), t(Simple), ts(ts), tt(NULL), ta(NULL), tc(tc) {}

TypeComposed::TypeComposed(TypeTuple *tt) :
l(1), t(Tuple), ts(NULL), tt(tt), ta(NULL), tc(NULL) {}

TypeComposed::TypeComposed(TypeTuple *tt, TypeComposed *tc) :
l(1 + tc->l), t(Tuple), ts(NULL), tt(tt), ta(NULL), tc(tc)  {}

TypeComposed::TypeComposed(TypeApp *ta) :
l(1), t(Application), ts(NULL), tt(NULL), ta(ta), tc(NULL) {}

TypeComposed::TypeComposed(TypeApp *ta, TypeComposed *tc) :
l(1 + tc->l), t(Application), ts(NULL), tt(NULL), ta(ta), tc(tc) {}

bool TypeComposed::areCorrectlyTyped(TypeComposed *typeComposed) {
    if (tc) {
        if (t != typeComposed->t)
            return false ;
        switch (t) {
            case Simple :
                return ts->isCorrectlyTyped(typeComposed->ts) && tc->areCorrectlyTyped(typeComposed->tc) ;
            case Tuple :
                return tt->isCorrectlyTyped(typeComposed->tt) && tc->areCorrectlyTyped(typeComposed->tc) ;
            case Application :
                return ta->isCorrectlyTyped(typeComposed->ta) && tc->areCorrectlyTyped(typeComposed->tc) ;
            assert(false) ;
        }
    }
    return true ;
}

bool TypeComposed::isCorrectlyTyped(TypeComposed *typeComposed) {
    return l == typeComposed->l && areCorrectlyTyped(typeComposed) ;
}

void TypeComposed::deleteType(TypeComposed *typeComposed) {
    if (typeComposed) {
        deleteType(typeComposed->tc) ;
        switch (typeComposed->t) {
            case Simple :
                delete typeComposed->ts ;
                break ;
            case Tuple :
                deleteType(typeComposed->tt) ;
                break ;
            case Application :
                deleteType(typeComposed->ta) ;
                break ;
            assert(false) ;
        }
        delete typeComposed ;
    }
}

TypeComposed::~TypeComposed() {
}

void TypeTuple::print(std::ostream& os, TypeComposed& typeComposed) {
    TypeTuple & typeTuple = (TypeTuple &) typeComposed ;
    switch (typeTuple.t) {
        case Simple :
            os << *typeTuple.ts ;
            break ;
        case Tuple :
            os << "(" << *typeTuple.tt << ")" ;
            break ;
        case Application :
            os << *typeTuple.ta ;
            break ;
        assert(false) ;
    }
    if (typeTuple.tc) {
	os << " * " ;
	print(os, *(typeTuple.tc)) ;
    }
}


std::ostream& operator<<(std::ostream& os, TypeTuple& typeTuple) {
    typeTuple.print(os, typeTuple) ;
    return os ;
}

TypeTuple::~TypeTuple() {
}

void TypeApp::print(std::ostream& os, TypeComposed& typeComposed) {
    TypeApp & typeApp = (TypeApp &) typeComposed ;
    switch (typeApp.t) {
        case Simple :
            os << *typeApp.ts ;
            break ;
        case Tuple :
            os << *typeApp.tt ;
            break ;
        case Application :
            os << "(" << *typeApp.ta << ")" ;
            break ;
        assert(false) ;
    }
    if (typeApp.tc) {
	os << " -> " ;
	print(os, *(typeApp.tc)) ;
    }
}


std::ostream& operator<<(std::ostream& os, TypeApp& typeApp) {
    typeApp.print(os, typeApp) ;
    return os ;
}

TypeApp::~TypeApp() {
}

Type::Type(TypeSimple* ts) : t(Simple), ts(ts), next(NULL) {}

Type::Type(TypeTuple* tt) : t(Tuple), tc(tt), next(NULL) {}

Type::Type(TypeApp* ta) : t(Application), tc(ta), next(NULL) {}

Type::Type(Type *orig) : t(orig->t), next(orig->next) {
    switch (t) {
        case Simple :
            ts = orig->ts ;
            break ;
        case Tuple : case Application :
            tc = orig->tc ;
            break ;
        default :
            assert(false) ;
    }
}

typeComposed Type::GetType() const {
    return t;
}

TypeSimple* Type::GetTypeSimple() const {
    return ts;
}

Type* Type::getNext() const {
    return next;
}

void Type::setNext(Type* next) {
    this->next = next;
}

Type* Type::Unification(Type *type1, Type *type2, AstVisInfer & infer) {
    
    if (type1 == type2)
        return type1 ;
    
    bool res = true ;
    Type * AC1 = type1, * AC2 = type2 ;
    while(AC2 && res) {
        if (AC1->t != AC2->t)
            res = false ;
        if (res) {
            if (AC1->t == Simple)
                res = AC1->ts->isCorrectlyTyped(AC2->ts) ;
            else
                res = AC1->tc->isCorrectlyTyped(AC2->tc) ;
        }
        if (!res)
            throw res ;
        Type *tmp1 = AC1, *tmp2 = AC2 ;
        AC1 = AC1->next ;
        if(!AC1)
            throw false ;
        AC2 = AC2->next ;
        infer.removeType(tmp1) ;
        infer.removeType(tmp2) ;
    }
    return AC1 ;
}

std::ostream& operator<<(std::ostream& os, const Type& type) {
    switch(type.t) {
        case Simple :
            os << *type.ts ;
            break ;
        case Tuple :
            os << (TypeTuple &)*type.tc ;
            break ;
        case Application :
            os << "(" << (TypeApp &)*type.tc << ")" ;
            break ;
        assert(false) ;
    }
    Type * next = type.next ;
    while(next) {
        os << " -> " ;
        switch(next->t) {
            case Simple :
                os << *next->ts ;
                break ;
            case Tuple :
                os << (TypeTuple &)*next->tc ;
                break ;
            case Application :
                os << "(" << (TypeApp &)*next->tc << ")" ;
                break ;
            assert(false) ;
        }
        next = next->next ;
    }
    return os;
}

void Type::deleteLink(Type* type) {
    if (type) {
        deleteLink(type->next) ;
        delete type ;
    }
}

void Type::deleteType(Type* type) {
    if (type) {
        switch(type->t) {
            case Simple :
                delete type->ts ;
                break ;
            case Tuple : case Application :
                TypeComposed::deleteType(type->tc) ;
                break ;
            assert(false) ;
        }
        delete type ;
    }
}

void Type::deleteTypeRec(Type* type, Type* fin) {
    if (type != fin) {
        deleteTypeRec(type->next, fin) ;
        deleteType(type) ;
    }
}

Type::~Type() {}
