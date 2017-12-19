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

class Strategy {
public:
    enum TAstVisitor {PRINTER, DESTRUCTOR, INFERATOR} ;
    enum Strat {TRAVERSAL, REVERSAL, ROUND_TRIP} ;
protected:
    AstVisitor * vis ;
    TAstVisitor typeAstVisitor ;
    Strat strat ;
public:
    Strategy();
    void setupStrategy(TAstVisitor typeAstVisitor);
    void setupStrategy(TAstVisitor typeAstVisitor, Strat strat);
    AstVisitor * getAstVis() const ;
    AstVisitor * setupAstVisitor () ;
    virtual ~Strategy();
};

#endif	/* STRATEGY_HPP */

