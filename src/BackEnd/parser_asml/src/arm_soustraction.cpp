#include "arm_soustraction.h"

namespace arm {

  arm_soustraction::arm_soustraction (void) {
    type_id = arm_instruction::SOUSTRACTION;
  }

  string arm_soustraction::get_instruction (void) {
    string instruction;
    auto get_mov = [](string var, string reg)->string{
      const char* c_var = var.c_str();
      string ret;
      int i_var;
      if (atoi(c_var) > ((1 << 8)-1)) {
        i_var = atoi(c_var) & ((1 << 16)-1);
        if (i_var != 0)
          ret += "\tmovw " + reg + ", #" + to_string(i_var) + "\n";
        if (atoi(c_var) > ((1 << 16)-1)) {
          i_var = atoi(c_var) >> 16;
          ret += "\tmovt " + reg + ", #" + to_string(i_var) + "\n";
        }
      } else {
        i_var = atoi(c_var);
        ret += "\tmov " + reg + ", #" + to_string(i_var) + "\n";
      }
      return ret;
    };
    instruction += "\tldr r0, [fp, #" + offset->find(op2)->second + "]\n";
    switch (arm_util::type_of(op3)) {
    case arm_util::DIRECT:
      //instruction += "\tmov r1, #" + op3 + "\n";
      instruction += get_mov(op3, "r1");
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
