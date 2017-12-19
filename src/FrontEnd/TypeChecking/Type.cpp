#include "Type.hpp"
#include <cassert>
#include <string>

Type::Type(TCode tc) :
tc(tc), var(""), value("") {}

Type::Type(const Type& orig) :
tc(orig.tc), var(orig.var) {}

Type::Type(TCode tc, std::string var) :
tc(tc), var(var), value("") {}

Type::Type(TCode tc, std::string var, std::string value) :
tc(tc), var(var), value(value) {}


std::string Type::getVar() const {
    return var;
}

std::string Type::print () {
    return (tc == TY_VAR ? "" : "- : ") + (tc == TY_FUN ? value : TCode_to_string()) + " =" ;
}

Type::~Type() {
}

std::string Type::TCode_to_string() {
    switch(tc) {
        case TY_ARRAY :
            return "array" ;
        case TY_BOOL :
            return "bool" ;
        case TY_FLOAT :
            return "float" ;
        case TY_FUN :
            return "<fun>" ;
        case TY_INT :
            return "int" ;
        case TY_TUPLE :
            return "" ;
        case TY_UNDEFINED :
            return "UNDEFINED" ;
        case TY_UNIT :
            return "unit" ;
        case TY_VAR :
            return "val " + var + std::string(" :") ; 
    }
    assert(false) ;
 }