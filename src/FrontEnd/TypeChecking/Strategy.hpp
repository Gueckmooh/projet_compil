/* 
 * File:   Strategy.hpp
 * Author: bleuzeb
 *
 * Created on 19 décembre 2017, 13:57
 */

#ifndef STRATEGY_HPP
#define	STRATEGY_HPP

#include "AstVisitor.hpp"

class Environment;


class AstVisitor;

class Strategy {
public:
    enum TAstVisitor {V_PRINTER, V_DESTRUCTOR, V_INFERATOR, V_TYPE_CHECKER} ;
    enum Strat {S_TRAVERSAL, S_REVERSAL, S_ROUND_TRIP} ;
protected:
    TAstVisitor typeAstVisitor ;
    Strat strat ;
    Environment *Env ;
public:
    Strategy(TAstVisitor typeAstVisitor);
    Strategy(TAstVisitor typeAstVisitor, Environment * Env);
    Strategy(TAstVisitor typeAstVisitor, Strat strat);
    AstVisitor * setupAstVisitor () ;
    virtual ~Strategy();
};

#endif	/* STRATEGY_HPP */

