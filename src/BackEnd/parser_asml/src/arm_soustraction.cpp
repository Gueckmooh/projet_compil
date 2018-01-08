#include "arm_soustraction.h"

namespace arm {

  arm_soustraction::arm_soustraction (void) {
    type_id = arm_instruction::SOUSTRACTION;
  }

  string arm_soustraction::get_instruction (void) {
    string instruction;
    instruction += "\tldr r0, [fp, #" + offset->find(op2)->second + "]\n";
    switch (arm_util::type_of(op3)) {
    case arm_util::DIRECT:
      instruction += "\tmov r1, #" + op3 + "\n";
      break;
    case arm_util::VARIABLE:
      instruction += "\tldr r1, [fp, #" + offset->find(op3)->second + "]\n";
      break;
    default:
      break;
    }
    instruction += "\tsub r0, r0, r1\n";
    if (op1.compare("0") != 0)
      instruction += "\tstr r0, [fp, #" + offset->find(op1)->second + "]\n";
    return instruction;
  }

  string arm_soustraction::get_op1 (void) {
    return op1;
  }

  string arm_soustraction::get_op2 (void) {
    return op2;
  }

  string arm_soustraction::get_op3 (void) {
    return op3;
  }

  void arm_soustraction::set_op1 (string op) {
    op1 = op;
  }

  void arm_soustraction::set_op2 (string op) {
    op2 = op;
  }

  void arm_soustraction::set_op3 (string op) {
    op3 = op;
  }

  int arm_soustraction::nb_regs (void) {
    return 2;
  }

  list<string>* arm_soustraction::get_op_list (void) {
    list<string>* l = new list<string> ();
    if (op1.compare("0") != 0)
      l->push_back(op1);
    l->push_back(op2);
    if (arm_util::type_of (op3) != arm_util::DIRECT)
    l->push_back(op3);
    l->sort();
    return l;
  }

}
