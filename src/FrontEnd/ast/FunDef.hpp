#include <string>
#include <list>
#include "AstNode.hpp"
#include "Type.hpp"
#ifndef FUN_DEF_H
#define FUN_DEF_H


class FunDef {
protected:
    std::string var_name;
    Type type;
    std::list<std::string> args_list;
    AstNode *body;
public:
    FunDef(std::string var_name, std::list<std::string> args_list, AstNode *body);
    ~FunDef();

};

#endif
