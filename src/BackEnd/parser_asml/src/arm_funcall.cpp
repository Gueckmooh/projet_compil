#include "arm_funcall.h"

namespace arm {

  arm_funcall::arm_funcall (void) {
    is_returning = false;
  }

  void arm_funcall::set_function_name (string name) {
    function_name = name;
  }

  void arm_funcall::set_retval (string ret) {
    retval = ret;
    is_returning = true;
  }

  string arm_funcall::get_retval (void) {
    return retval;
  }

  bool arm_funcall::immediate (string instr) {
    char c = instr.front();
    return c >= '0' && c <= '9';
  }

  string arm_funcall::get_instruction (void) {
    string instruction;
    int nb = params.size();
    int size = params.size();
    string var1, varn;
    vector<string>::reverse_iterator it = params.rbegin();
    var1 = *it;
    while (it != params.rend()) {
      if (nb > 4) {
	if (immediate (*it))
	  instruction += "\tmov r0, #" + (*it) + "\n";
	else
	  instruction += "\tldr r0, [fp, #" + offset->find(*it)->second + "]\n";
	instruction += "\tstr r0, [sp, #" + to_string(-8-(size-nb)*4) + "]\n";
	nb--;
      } else {
	if (immediate (*it))
	  instruction += "\tmov r" + to_string(nb-1) + ", #" + (*it) + "\n";
	else
	  instruction += "\tldr r" + to_string(nb-1) + ", [fp, #" + offset->find(*it)->second + "]\n";
	nb--;
      }
      it++;
    }
    instruction += "\tbl " + function_name + "\n";
    if (is_returning) {
      instruction += "\tstr r0, [fp, #" + offset->find(retval)->second + "]\n";
    }
    return instruction;
  }

}
