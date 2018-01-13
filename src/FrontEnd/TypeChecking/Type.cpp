#include "Type.hpp"
#include "TypeFactory.hpp"
#include "AstVisTypeChecking.hpp"
#include <cassert>

std::ostream * TypeSimple::os = NULL ;
char TypeSimple::next_poly = 'a' ;
PolyMap TypeSimple::PM = {} ;

TypeSimple::TypeSimple(typeSimple ts) :
ts(ts), poly(next_poly) {
    if (ts == POLY && PM.find(poly) == PM.end()) {
        PM[next_poly++] = NULL ;
    }
}

TypeSimple::TypeSimple(typeSimple ts, char poly) :
ts(ts), poly(poly) {}

char TypeSimple::getPoly() const {
    return poly;
}

char TypeSimple::getNextPoly() {
    return next_poly ;
}

void TypeSimple::resetNextPoly() {
    next_poly = 'a' ;
}

Type * TypeSimple::getMappedPoly(char poly) {
    PolyMap::iterator it = PM.find(poly) ;
    if (it != PM.end())
        return it->second ;
    else {
        *os << "UNBOUND POLYMORPHIC TYPE '" << poly << std::endl ;
        throw false ;
    }
}

void TypeSimple::mapPoly(char poly, Type* type) {
    PM[poly] = type ;
}

void TypeSimple::printPoly() {
    *os << "Polymorphic Types Map : [" ;
    PolyMap::iterator it = PM.begin() ;
    if (it != PM.end()) {
        *os << "'" << it->first << " : " ;
        if(it->second)
            *os << *it->second ;
        else
            *os << "NULL" ;
        it++ ;
    }
    
    for (; it != PM.end() ; it++) {
        *os << ", " << "'" << it->first << " : " ;
        if(it->second)
            *os << *it->second ;
        else
            *os << "NULL" ;
    }
    *os << "]" ;
}

void TypeSimple::resetPoly() {
    PolyMap::iterator it = PM.begin() ;
    while (it != PM.end()) {
        Type::deleteTypeRec(it->second);
        it->second = NULL ;
        it++ ;
    }
}

void TypeSimple::clearPolyMap() {
    PolyMap::iterator it = PM.begin() ;
    while (it != PM.end()) {
        Type::deleteTypeRec(it->second);
        PM.erase(it) ;
        it++ ;
    }
    next_poly = 'a' ;
}

void TypeSimple::setOs(std::ostream* os) {
    TypeSimple::os = os ;
}


typeSimple TypeSimple::getType() const {
    return ts;
}

bool TypeSimple::isCorrectlyTyped(TypeSimple *typeSimple) {
    if (ts == typeSimple->ts) {
        if (ts == POLY)
            return poly == typeSimple->poly ;
        return true ;
    }
    return false ;
}

TypeSimple* TypeSimple::copyTypeSimple(TypeSimple* typeSimple) {
    return new TypeSimple(typeSimple->ts, typeSimple->poly) ;
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
        case POLY :
            type_str = "'" + std::string(1, typeSimple.poly) ;
            break ;
        assert(false) ;
        
    }
    return os << type_str ;
}

TypeSimple::~TypeSimple() {}

TypeComposed::TypeComposed(TypeSimple *ts) :
l(1), t(ts->getType() == POLY ? Polymorphe : Simple), ts(ts), tt(NULL), ta(NULL), tc(NULL)  {}

TypeComposed::TypeComposed(TypeSimple *ts, unsigned l) :
l(l), t(ts->getType() == POLY ? Polymorphe : Simple), ts(ts), tt(NULL), ta(NULL), tc(NULL)  {}

TypeComposed::TypeComposed(TypeSimple *ts, TypeComposed *tc) :
l(1 + tc->l), t(ts->getType() == POLY ? Polymorphe : Simple), ts(ts), tt(NULL), ta(NULL), tc(tc) {}

TypeComposed::TypeComposed(TypeTuple *tt) :
l(1), t(Tuple), ts(NULL), tt(tt), ta(NULL), tc(NULL) {}

TypeComposed::TypeComposed(TypeTuple *tt, TypeComposed *tc) :
l(1 + tc->l), t(Tuple), ts(NULL), tt(tt), ta(NULL), tc(tc)  {}

TypeComposed::TypeComposed(TypeApp *ta) :
l(1), t(Application), ts(NULL), tt(NULL), ta(ta), tc(NULL) {}

TypeComposed::TypeComposed(TypeApp *ta, TypeComposed *tc) :
l(1 + tc->l), t(Application), ts(NULL), tt(NULL), ta(ta), tc(tc) {}

unsigned TypeComposed::size() const {
    return l ;
}

typeComposed TypeComposed::getType() const {
    return t;
}

TypeSimple* TypeComposed::getSimple() const {
    return ts;
}

TypeTuple* TypeComposed::getTuple() const {
    return tt;
}

TypeApp* TypeComposed::getApp() const {
    return ta;
}

TypeComposed* TypeComposed::getNext() const {
    return tc;
}

void TypeComposed::setNext(TypeComposed* tc) {
    this->tc = tc;
}

bool TypeComposed::areCorrectlyTyped(TypeComposed *typeComposed) {
    if (tc) {
        if (t != typeComposed->t)
            return false ;
        switch (t) {
            case Simple : case Polymorphe :
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
            case Simple : case Polymorphe :
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
        case Simple : case Polymorphe :
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

TypeTuple* TypeTuple::copyTypeTuple(TypeTuple* typeTuple) {
    if (typeTuple->l == 1) {
        switch (typeTuple->t) {
            case Simple : case Polymorphe :
                return new TypeTuple(TypeSimple::copyTypeSimple(typeTuple->ts)) ;
            case Tuple :
                return new TypeTuple(copyTypeTuple(typeTuple->tt)) ;
            case Application :
                assert(false) ;
        }
    }
    TypeTuple * next = copyTypeTuple((TypeTuple *)typeTuple->tc) ;
    switch (typeTuple->t) {
        case Simple : case Polymorphe :
            return new TypeTuple(TypeSimple::copyTypeSimple(typeTuple->ts), next) ;
        case Tuple :
            return new TypeTuple(copyTypeTuple(typeTuple->tt), next) ;
        case Application :
            return new TypeTuple(TypeApp::copyTypeApp(typeTuple->ta), next) ;
        default :
            assert(false) ;
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
        case Simple : case Polymorphe :
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

TypeApp* TypeApp::copyTypeApp(TypeApp* typeApp) {
    if (typeApp->l == 1)
        switch (typeApp->t) {
            case Simple : case Polymorphe :
                return new TypeApp(TypeSimple::copyTypeSimple(typeApp->ts)) ;
            case Tuple :
                return new TypeApp(TypeTuple::copyTypeTuple(typeApp->tt)) ;
            case Application :
                assert(false) ;
        }
    TypeApp * next = copyTypeApp((TypeApp*)typeApp->tc) ;
    switch (typeApp->t) {
        case Simple : case Polymorphe :
            return new TypeApp(TypeSimple::copyTypeSimple(typeApp->ts), next) ;
        case Tuple :
            return new TypeApp(TypeTuple::copyTypeTuple(typeApp->tt), next) ;
        case Application :
            return new TypeApp(copyTypeApp(typeApp->ta), next) ;
        default :
            assert(false) ;
    }
}


std::ostream& operator<<(std::ostream& os, TypeApp& typeApp) {
    typeApp.print(os, typeApp) ;
    return os ;
}

TypeApp::~TypeApp() {
}

Type::Type(TypeSimple* ts) : t(ts->getType() == POLY ? Polymorphe : Simple), ts(ts), next(NULL) {}

Type::Type(TypeTuple* tt) : t(Tuple), tc(tt), next(NULL) {}

Type::Type(TypeApp* ta) :  t(Application), tc(ta), next(NULL) {}

typeComposed Type::GetType() const {
    return t;
}

void Type::SetType(typeComposed t) {
    this->t = t ;
}

TypeSimple* Type::GetTypeSimple() const {
    return ts;
}

void Type::SetTypeSimple(TypeSimple* ts) {
    this->ts = ts ;
}

TypeComposed* Type::GetTypeComposed() const {
    return tc ;
}

void Type::SetTypeComposed(TypeComposed *tc) {
    this->tc = tc ;
}

Type* Type::getNext() const {
    return next;
}

void Type::setNext(Type* next) {
    this->next = next;
}

Type* Type::Unification(Type *typeApp, Type *typeArgs) {
    if (typeArgs) {
        
        if (!typeApp) {
            std::cout << "APPLIED TOO MANY ARGUMENTS" << std::endl ;
            throw false ;
        }
        
        if (typeApp->t == Polymorphe) {
            if(!TypeSimple::getMappedPoly(typeApp->GetTypeSimple()->getPoly()))
                TypeSimple::mapPoly(typeApp->GetTypeSimple()->getPoly(), Type::copyType(typeArgs)) ;
            Type * Poly = Type::copyType(TypeSimple::getMappedPoly(typeApp->GetTypeSimple()->getPoly())) ;
            Type * tmp = typeApp ;
            Poly->setNext(typeApp->getNext()) ;
            typeApp = Poly ;
            Type::deleteType(tmp) ;
        }
        
        else if (typeArgs->t == Polymorphe) {
            if(!TypeSimple::getMappedPoly(typeArgs->GetTypeSimple()->getPoly()))
                TypeSimple::mapPoly(typeArgs->GetTypeSimple()->getPoly(), Type::copyType(typeApp)) ;
            Type * Poly = Type::copyType(TypeSimple::getMappedPoly(typeArgs->GetTypeSimple()->getPoly())) ;
            Type * tmp = typeArgs ;
            Poly->setNext(typeArgs->getNext()) ;
            typeArgs = Poly ;
            Type::deleteType(tmp) ;
        }
        
        if(typeApp->t != typeArgs->t) {
            std::cout << "ERROR TYPE :" << std::endl ;
            throw false ;
        }
        
        bool res ;
        if (typeArgs->t == Simple || typeArgs->t == Polymorphe)
            res = typeApp->ts->isCorrectlyTyped(typeArgs->ts) ;
        else
            res = typeApp->tc->isCorrectlyTyped(typeArgs->tc) ;
        if (!res) {
            std::cout << "MISMATCH UNIFICATION" << std::endl ;
            throw false ;
        }
        Type *tmpApp = typeApp, *tmpArgs = typeArgs ;
        typeApp = typeApp->getNext() ;
        typeArgs = typeArgs->getNext() ;
        Type::deleteType(tmpApp) ;
        Type::deleteType(tmpArgs) ;
        return Unification(typeApp, typeArgs) ;
        
    }
    return typeApp ;
}

void Type::printApplication(std::ostream& os, Type& type) {
    switch(type.t) {
        case Simple : case Polymorphe :
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
    if (type.next) {
        os << " -> " ;
        printApplication(os, *type.next) ;
    }
    
}

std::ostream& operator<<(std::ostream& os, Type& type) {
    type.printApplication(os, type) ;
    return os;
}

Type* Type::copyType(Type* orig) {
    switch (orig->t) {
        case Simple : case Polymorphe :
            return new Type(TypeSimple::copyTypeSimple(orig->ts)) ;
        case Tuple :
            return new Type(TypeTuple::copyTypeTuple((TypeTuple *) orig->tc)) ;
        case Application :
            return new Type(TypeApp::copyTypeApp((TypeApp *) orig->tc)) ;
        default :
            assert(false) ;
    }
}

Type* Type::copyTypeRec(Type* orig) {
    if (!orig->getNext())
        return copyType(orig) ;
    Type * next = copyTypeRec(orig->getNext()) ;
    Type * copy = copyType(orig) ;
    copy->setNext(next) ;
    return copy ;
         
}

void Type::deleteType(Type* type) {
    if (type) {
        switch(type->t) {
            case Simple : case Polymorphe :
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

void Type::deleteTypeRec(Type* type) {
    if (type) {
        deleteTypeRec(type->next) ;
        deleteType(type) ;
    }
}

Type::~Type() {}
