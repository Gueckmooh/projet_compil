#ifndef TYPE_H
#define TYPE_H

#include "type.h"
#include <string>

class Type {
protected:
    TCode tc ;
    std::string var ;
    std::string value ;
    std::string TCode_to_string();
public:
    Type(TCode tc);
    Type(const Type & orig);
    Type(TCode tc, std::string var);
    Type(TCode tc, std::string var, std::string value);
    std::string getVar() const;
    std::string print() ;
    ~Type();;
};


#endif
