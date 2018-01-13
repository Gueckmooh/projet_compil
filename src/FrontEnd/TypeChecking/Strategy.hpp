/* 
 * File:   Strategy.hpp
 * Author: bleuzeb
 *
 * Created on 19 décembre 2017, 13:57
 */

#ifndef STRATEGY_HPP
#define	STRATEGY_HPP

#include "AstVisitor.hpp"

class AstVisitor;
class Environment;

enum Visitor {V_PRINTER, V_DESTRUCTOR, V_TYPE_CHECKER} ;
enum Strat {S_PREFIX, S_INFIX, S_POSTFIX} ;

class Strategy {
protected:
    Visitor typeAstVisitor ;
    Strat strat ;
    Environment *Env ;
public:
    Strategy(Visitor typeAstVisitor);
    Strategy(Visitor typeAstVisitor, Environment * Env);
    Strategy(Visitor typeAstVisitor, Strat strat);
    AstVisitor * setupAstVisitor () ;
    virtual ~Strategy();
};

#endif	/* STRATEGY_HPP */

