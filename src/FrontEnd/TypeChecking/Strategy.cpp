#include "Strategy.hpp"
#include "AstVisitor.hpp"
#include "AstVisTypeChecking.hpp"
#include <cassert>

Strategy::Strategy(TAstVisitor typeAstVisitor) :
typeAstVisitor(typeAstVisitor), strat(S_TRAVERSAL), Env(NULL) {}

Strategy::Strategy(TAstVisitor typeAstVisitor, Environment * Env) :
typeAstVisitor(typeAstVisitor), Env(Env) {}

Strategy::Strategy(TAstVisitor typeAstVisitor, Strat strat) :
typeAstVisitor(typeAstVisitor), strat(strat), Env(NULL) {}

AstVisitor * Strategy::setupAstVisitor() {
    AstVisAbstract * prior, * feedback ;
    AstVisitor *AstVis ;
    switch(typeAstVisitor) {
        case V_TYPE_CHECKER :
            prior = new AstVisExplore(Env) ;
            feedback = new AstVisInfer(Env) ;
            break ;
        case V_DESTRUCTOR :
            prior = new AstVisGhost() ;
            feedback = new AstVisDestruct() ;
            break ;
        case V_INFERATOR :
            prior = new AstVisGhost() ;
            feedback = new AstVisInfer(Env) ;
            break;
        case V_PRINTER :
            switch(strat) {
                case S_TRAVERSAL :
                    prior = new AstVisPrint() ;
                    feedback = new AstVisGhost() ;
                    break ;
                case S_REVERSAL :
                    prior = new AstVisGhost() ;
                    feedback = new AstVisPrint() ;
                    break ;
                case S_ROUND_TRIP :
                    prior = new AstVisPrint() ;
                    feedback = new AstVisPrint() ;
                default :
                    assert(false) ;
            }
            break;
        default:
             assert(false) ;
    }       
    AstVis = new AstVisitor(prior, feedback) ;
    prior->setAstVis(AstVis) ;
    feedback->setAstVis(AstVis) ; 
    return AstVis ;
}

Strategy::~Strategy() {
}

