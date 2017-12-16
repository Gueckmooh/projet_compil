#include "arm_instruction_factory.h"

namespace arm {

  arm_instruction* arm_instruction_factory::create_instruction (asml_instruction* instr) {
    switch (instr->get_type()) {
    case asml_instruction::FUNCALL:
      return create_funcall (dynamic_cast<asml_funcall*>(instr));
    case asml_instruction::AFFECTATION:
      return create_affectation (dynamic_cast<asml_affectation*>(instr));
    case asml_instruction::ADDITION:
      return create_addition (dynamic_cast<asml_addition*>(instr));
      break;
    case asml_instruction::SOUSTRACTION:
      return create_soustraction (dynamic_cast<asml_soustraction*>(instr));
    default:
      return NULL;
    }
  }

  arm_funcall* arm_instruction_factory::create_funcall (asml_funcall* fun) {
    arm_funcall* funcall = new arm_funcall ();
    funcall->set_function_name ((fun->get_funcname()).substr(1));
    for (vector<string>::iterator it = fun->begin();
	 it != fun->end();
	 it++) {
      funcall->add_param(*it);
    }
    if (fun->is_returning()) {
      funcall->set_retval (fun->get_retval());
    }
    return funcall;
  }

  arm_affectation* arm_instruction_factory::create_affectation (asml_affectation* aff) {
    arm_affectation* affectation = new arm_affectation ();
    affectation->set_op1(aff->get_op1());
    affectation->set_op2(aff->get_op2());
    return affectation;
  }

  arm_addition* arm_instruction_factory::create_addition (asml_addition* add) {
    arm_addition* addition = new arm_addition ();
    addition->set_op1(add->get_op1());
    addition->set_op2(add->get_op2());
    addition->set_op3(add->get_op3());
    return addition;
  }

  arm_soustraction* arm_instruction_factory::create_soustraction (asml_soustraction* add) {
    arm_soustraction* soustraction = new arm_soustraction ();
    soustraction->set_op1(add->get_op1());
    soustraction->set_op2(add->get_op2());
    soustraction->set_op3(add->get_op3());
    return soustraction;
  }

}
