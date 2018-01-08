#include "arm_affectation.h"
#include "arm_function.h"

namespace arm {

  arm_affectation::arm_affectation (void) {
    type_id = arm_instruction::AFFECTATION;
  }

  string arm_affectation::get_instruction (void) {
    string instruction;
    switch (arm_util::type_of(op2)) {
    case arm_util::DIRECT:
      instruction += "\tmov r0, #" + op2 + "\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r0, [fp, #" + offset->find(op2)->second + "]\n";
      break;
    case arm_util::LABEL:
      instruction += "\tldr r0, " + arm_function::add_ref(op2) + "\n";
    default:
      break;
    }
    if (op1.compare("0") != 0)
      instruction += "\tstr r0, [fp, #" + offset->find(op1)->second + "]\n";
    return instruction;
  }

  void arm_affectation::set_op1 (string op) {
    op1 = op;
  }

  void arm_affectation::set_op2 (string op) {
    op2 = op;
  }

  string arm_affectation::get_op1 (void) {
    return op1;
  }

  string arm_affectation::get_op2 (void) {
    return op2;
  }

  int arm_affectation::nb_regs (void) {
    return 3;
  }

  list<string>* arm_affectation::get_op_list (void) {
    list<string>* l = new list<string> ();
    if (op1.compare("0") != 0)
      l->push_back(op1);
    if (arm_util::type_of (op2) != arm_util::DIRECT)
    l->push_back(op2);
    l->sort();
    return l;
  }

}
