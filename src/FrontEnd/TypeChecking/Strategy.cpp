/**
 * \file      Strategy.cpp
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Strategy Factory to choose iteration and process mode for Ast
 *
 */

#include "Strategy.hpp"
#include "AstVisitor.hpp"
#include "AstVisTypeChecking.hpp"
#include <cassert>

Strategy::Strategy(Visitor typeAstVisitor) :
typeAstVisitor(typeAstVisitor), strat(S_PREFIX), Env(NULL) {}

Strategy::Strategy(Visitor typeAstVisitor, Environment * Env) :
typeAstVisitor(typeAstVisitor), Env(Env) {}

Strategy::Strategy(Visitor typeAstVisitor, Strat strat) :
typeAstVisitor(typeAstVisitor), strat(strat), Env(NULL) {}

AstVisitor * Strategy::setupAstVisitor() {
    AstVisAbstract *prefix, *infix, *postfix ;
    AstVisitor *AstVis ;
    switch(typeAstVisitor) {
        case V_TYPE_CHECKER :
            prefix = new AstVisExplore(Env) ;
            infix = new AstVisRangeLet(Env) ;
            postfix = new AstVisInfer(Env) ;
            break ;
        case V_DESTRUCTOR :
            prefix = new AstVisGhost() ;
            infix = new AstVisGhost () ;
            postfix = new AstVisDestruct() ;
            break ;
        case V_PRINTER :
            switch(strat) {
                case S_PREFIX :
                    prefix = new AstVisPrint() ;
                    infix = new AstVisGhost () ;
                    postfix = new AstVisGhost() ;
                    break ;
                case S_INFIX :
                    prefix = new AstVisGhost() ;
                    infix = new AstVisPrint() ;
                    postfix = new AstVisGhost() ;
                    break ;
                case S_POSTFIX :
                    prefix = new AstVisGhost () ;
                    infix = new AstVisGhost () ;
                    postfix = new AstVisPrint() ;
                    break ;
                default :
                    assert(false) ;
            }
            break;
        default:
             assert(false) ;
    }       
    AstVis = new AstVisitor(prefix, infix, postfix) ;
    prefix->setAstVis(AstVis) ;
    infix->setAstVis(AstVis) ;
    postfix->setAstVis(AstVis) ; 
    return AstVis ;
}

Strategy::~Strategy() {}

