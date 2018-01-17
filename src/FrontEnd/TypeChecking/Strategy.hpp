/**
 * \file      Strategy.hpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Strategy Factory to choose iteration and process mode for Ast
 * \details
 * this file defined an Strategy Factory to abstract iteration mode and process mode for Ast
 * the strategies are the following iteration travels : PREFIX, INFIX, POSTFIX
 * the process is delegated to an AstVisitor built by the Strategy Factory among these three :
 * Printer and Destructor (secondary) and TypeChecker (which process TypeChecking) 
 */
 
#ifndef STRATEGY_HPP
#define	STRATEGY_HPP

#include "AstVisitor.hpp"

class AstVisitor;
class Environment;

enum Visitor {V_PRINTER, V_DESTRUCTOR, V_TYPE_CHECKER} ;
enum Strat {S_PREFIX, S_INFIX, S_POSTFIX} ;

/* !
 * \class Strategy
 */

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

