#include "arm_boolean.h"

namespace arm {

  arm_boolean::arm_boolean (int type) {
    type_id = type;
    switch (type) {
    case LT:
      cmp = "bge";
      break;
    case GT:
      cmp = "ble";
      break;
    case LE:
      cmp = "bgt";
      break;
    case GE:
      cmp = "blt";
      break;
    case EQUAL:
      cmp = "bne";
      break;
    case NEQUAL:
      cmp = "beq";
    default:
      break;
    }
  }

  string arm_boolean::get_instruction (void) {
    string instruction;
    switch (arm_util::type_of(op1)) {
    case arm_util::VARIABLE:
      instruction += "\tldr r0, [fp, #" + offset->find(op1)->second + "]\n";
      break;
    case arm_util::DIRECT:
      instruction += "\tmov r0, " + op1 + "\n";
      break;
    default:
      break;
    }
    switch (arm_util::type_of(op2)) {
    case arm_util::VARIABLE:
      instruction += "\tldr r1, [fp, #" + offset->find(op2)->second + "]\n";
      instruction += "\tcmp r0, r1\n";
      break;
    case arm_util::DIRECT:
      instruction += "\tcmp r0, #" + op2 + "\n";
      break;
    default:
      break;
    }
    instruction += "\t" + cmp + " " + lFalse + "\n";
    return instruction;
  }

  int arm_boolean::get_type (void) {
    return type_id;
  }

  void arm_boolean::set_op1 (string op) {
    op1 = op;
  }

  void arm_boolean::set_op2 (string op) {
    op2 = op;
  }

  void arm_boolean::set_lFalse (string l) {
    lFalse = l;
  }

  string arm_boolean::get_op1 (void) {
    return op1;
  }

  string arm_boolean::get_op2 (void) {
    return op2;
  }

  int arm_boolean::nb_regs (void) {
    switch (arm_util::type_of(op2)) {
    case arm_util::VARIABLE:
      return 2;
    case arm_util::DIRECT:
      return 3;
    default:
      return 0;
    }
  }

  list<string>* arm_boolean::get_op_list (void) {
    list<string>* l = new list<string> ();
    if (arm_util::type_of(op1) != arm_util::DIRECT)
      l->push_back(op1);
    if (arm_util::type_of(op2) != arm_util::DIRECT)
      l->push_back(op2);
    l->sort();
    return l;
  }

}
