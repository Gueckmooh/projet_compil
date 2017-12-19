#ifndef ASTVISINFER_HPP
#define ASTVISINFER_HPP

#include "AstVisitor.hpp"
#include <map>
#include <stack>

class AstVisPrint;

typedef std::map<const std::string, std::string> EnvironmentMap ;
typedef std::stack<EnvironmentMap> CurrentEnvironment ;

class AstVisInfer : public AstVisPrint {
protected:
    EnvironmentMap EM = {
        {"print_int", "int -> unit"}
    } ;
    CurrentEnvironment CE ;
public:
    AstVisInfer();
    virtual ~AstVisInfer() ;
    void print(AstNode& node) override;
    bool isCorrectlyTyped (AstNode& node) ;
};

#endif /* ASTVISINFER_HPP */

