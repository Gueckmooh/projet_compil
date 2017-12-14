#include "AstNode.hpp"
#include "AstNodeUnit.hpp"
#include "AstNodeBool.hpp"
#include "AstNodeInt.hpp"
#include "AstNodeFloat.hpp"
#include "AstNodeNot.hpp"
#include "AstNodeNeg.hpp"
#include "AstNodeFneg.hpp"
#include "AstNodeAdd.hpp"
#include "AstNodeSub.hpp"
#include "AstNodeFadd.hpp"
#include "AstNodeFsub.hpp"
#include "AstNodeFmul.hpp"
#include "AstNodeFdiv.hpp"
#include "AstNodeEq.hpp"
#include "AstNodeLe.hpp"
#include "AstNodeArray.hpp"
#include "AstNodeGet.hpp"
#include "AstNodeIf.hpp"
#include "AstNodePut.hpp"
#include "AstNodeLet.hpp"
#include "AstNodeVar.hpp"
#include "AstNodeLetRec.hpp"
#include "AstNodeApp.hpp"
#include "AstNodeTuple.hpp"
#include "AstNodeLetTuple.hpp"
#include "FunDef.hpp"

#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "type.h"
#include "ast.h"
#include "assert.h"
#include "string.h"
#include "utils.h"
#include "config.h"

AstNode* build_ast(ptree t){
    assert(t);
    AstNode *result = NULL;
    switch(t->code) {
        case T_UNIT :
            result = new AstNodeUnit();
            break;
        case T_BOOL :
            result = new AstNodeBool(t->params.b);
            break;
        case T_INT :
            result = new AstNodeInt(t->params.i);
            break;
        case T_FLOAT :
            result = new AstNodeFloat(t->params.f);
            break;
        case T_NOT :
            result = new AstNodeNot(build_ast(t->params.t));
            break;
        case T_NEG :
            result = new AstNodeNeg(build_ast(t->params.t));
            break;
        case T_FNEG :
            result = new AstNodeFneg(build_ast(t->params.t));
            break;
        case T_ADD :
            result = new AstNodeAdd(build_ast(t->params.tbinary.t1),
                              build_ast(t->params.tbinary.t2));
            break;
        case T_SUB :
            result = new AstNodeSub(build_ast(t->params.tbinary.t1),
                              build_ast(t->params.tbinary.t2));
            break;
        case T_FADD :
            result = new AstNodeFadd(build_ast(t->params.tbinary.t1),
                               build_ast(t->params.tbinary.t2));
            break;
        case T_FSUB :
            result = new AstNodeFsub(build_ast(t->params.tbinary.t1),
                               build_ast(t->params.tbinary.t2));
        case T_FMUL :
            result = new AstNodeFmul(build_ast(t->params.tbinary.t1),
                               build_ast(t->params.tbinary.t2));
            break;
        case T_FDIV :
            result = new AstNodeFdiv(build_ast(t->params.tbinary.t1),
                               build_ast(t->params.tbinary.t2));
            break;
        case T_EQ :
            result = new AstNodeEq(build_ast(t->params.tbinary.t1),
                             build_ast(t->params.tbinary.t2));
            break;
        case T_LE :
            result = new AstNodeLe(build_ast(t->params.tbinary.t1),
                             build_ast(t->params.tbinary.t2));
            break;
        case T_ARRAY :
            result = new AstNodeArray(build_ast(t->params.tbinary.t1),
                                build_ast(t->params.tbinary.t2));
            break;
        case T_GET :
            result = new AstNodeGet(build_ast(t->params.tbinary.t1),
                              build_ast(t->params.tbinary.t2));
            break;
        case T_IF :
            result = new AstNodeIf(build_ast(t->params.tternary.t1),
                                   build_ast(t->params.tternary.t2),
                                   build_ast(t->params.tternary.t3));
            break;
        case T_PUT :
            result = new AstNodePut(build_ast(t->params.tternary.t1),
                                    build_ast(t->params.tternary.t2),
                                    build_ast(t->params.tternary.t3));
            break;
        case T_LET :
            result = new AstNodeLet(build_ast(t->params.tlet.t1),
                                    build_ast(t->params.tlet.t2),
                                    to_cpp_string(t->params.tlet.v));
            break;
        case T_VAR :
            result = new AstNodeVar(to_cpp_string(t->params.v));
            break;
        case T_LETREC :
            result = new AstNodeLetRec(new FunDef(to_cpp_string(t->params.tletrec.fd->var),
                                        to_cpp_str_list(t->params.tletrec.fd->args),
                                        build_ast(t->params.tletrec.fd->body)
                                       ),
                                 build_ast(t->params.tletrec.t));
            break;
        case T_APP :
            result = new AstNodeApp(to_cpp_str_list(t->params.tapp.l),
                              build_ast(t->params.tapp.t));
            break;
        case T_TUPLE :
            result = new AstNodeTuple(to_cpp_str_list(t->params.ttuple.l));
            break;
        case T_LETTUPLE :
            result = new AstNodeLetTuple(to_cpp_str_list(t->params.lettuple.l),
                                   build_ast(t->params.lettuple.t1),
                                   build_ast(t->params.lettuple.t2));
            break;
        default:
             printf("Error in build_ast. tree node code = %d\n ", t->code);
             assert(false);
    }
    return result;
}
