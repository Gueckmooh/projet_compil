#include "Strategy.hpp"
#include "AstVisitor.hpp"
#include "AstVisInfer.hpp"
#include <cassert>

Strategy::Strategy() : vis(NULL), strat(TRAVERSAL) {
}

void Strategy::setupStrategy(TAstVisitor typeAstVisitor) {
    this->typeAstVisitor = typeAstVisitor ;
}

void Strategy::setupStrategy(TAstVisitor typeAstVisitor, Strat strat) {
    setupStrategy(typeAstVisitor) ;
    this->strat = strat ;
}

AstVisitor* Strategy::getAstVis() const {
    return vis ;
}


AstVisitor* Strategy::setupAstVisitor() {
    if (vis) {
	delete vis ;
    }
    AstVisAbstract * prior, * feedback ;
    switch(typeAstVisitor) {
	case DESTRUCTOR :
	    prior = new AstVisGhost() ;
	    feedback = new AstVisDestruct() ;
	    break ;
	case INFERATOR :
	    prior = new AstVisGhost() ;
	    feedback = new AstVisInfer() ;
	    break ;
	case PRINTER :
	    switch(strat) {
		case TRAVERSAL :
		    prior = new AstVisPrint() ;
		    feedback = new AstVisGhost() ;
		    break ;
		case REVERSAL :
		    prior = new AstVisGhost() ;
		    feedback = new AstVisPrint() ;
		    break ;
		case ROUND_TRIP :
		    prior = new AstVisPrint() ;
		    feedback = new AstVisPrint() ;
	    }
	    break ;
	assert(false) ;    
    }    
    vis = new AstVisitor(prior, feedback) ;
    prior->setAstVist(vis) ;
    feedback->setAstVist(vis) ;

    return vis ;
}

Strategy::~Strategy() {
    delete vis ;
}

