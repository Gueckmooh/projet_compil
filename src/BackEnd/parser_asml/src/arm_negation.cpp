#include "arm_negation.h"

namespace arm {

  arm_negation::arm_negation (void) {
    type_id = arm_instruction::NEGATION;
  }

  string arm_negation::get_instruction (void) {
    string instruction;
    instruction += "\tldr r0, [fp, #" + offset->find(op2)->second + "]\n";
    instruction += "\trsb r0, r0, #0\n";
    if (op1.compare("0") != 0)
      instruction += "\tstr r0, [fp, #" + offset->find(op1)->second + "]\n";
    return instruction;
  }

  string arm_negation::get_op1 (void) {
    return op1;
  }

  string arm_negation::get_op2 (void) {
    return op2;
  }

  void arm_negation::set_op1 (string op) {
    op1 = op;
  }

  void arm_negation::set_op2 (string op) {
    op2 = op;
  }

  int arm_negation::nb_regs (void) {
    return 3;
  }

  list<string>* arm_negation::get_op_list (void) {
    list<string>* l = new list<string> ();
    l->push_back(op1);
    l->push_back(op2);
    l->sort();
    return l;
  }

}
