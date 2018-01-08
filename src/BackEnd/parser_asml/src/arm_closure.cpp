#include "arm_closure.h"

namespace arm {

  arm_closure::arm_closure (void) {
    type_id = arm_instruction::CLOSURE;
    do_return = false;
  }

  string arm_closure::get_value (void) {
    return value;
  }

  void arm_closure::set_return (string var) {
    return_variable = var;
    do_return = true;
  }

  void arm_closure::unset_return (void) {
    do_return = false;
  }

  bool arm_closure::is_returning (void) {
    return do_return;
  }

  string arm_closure::get_retval (void) {
    return return_variable;
  }

  void arm_closure::set_value (string name) {
    value = name;
  }

  void arm_closure::add_param (string param) {
    params.push_back(param);
  }

  vector<string>::iterator arm_closure::begin (void) {
    return params.begin();
  }

  vector<string>::iterator arm_closure::end (void) {
    return params.end();
  }

  int arm_closure::size (void) {
    return params.size();
  }

  string arm_closure::operator[] (int t) {
    return params[t];
  }

  string arm_closure::get_instruction (void) {
    string instruction;
    int nb = params.size();
    int size = params.size();
    string var1, varn;
    vector<string>::reverse_iterator it = params.rbegin();
    if (!params.empty()) {
      var1 = *it;
      while (it != params.rend()) {
	if (nb > 4) {
	  if (arm_util::type_of (*it) == arm_util::DIRECT)
	    instruction += "\tmov r0, #" + (*it) + "\n";
	  else
	    instruction += "\tldr r0, [fp, #" + offset->find(*it)->second + "]\n";
	  instruction += "\tstr r0, [sp, #" + to_string(-8-(size-nb)*4) + "]\n";
	  nb--;
	} else {
	  if (arm_util::type_of (*it) == arm_util::DIRECT)
	    instruction += "\tmov r" + to_string(nb-1) + ", #" + (*it) + "\n";
	  else
	    instruction += "\tldr r" + to_string(nb-1) + ", [fp, #" + offset->find(*it)->second + "]\n";
	  nb--;
	}
	it++;
      }
    }
    instruction += "\tldr r7, [fp, #" + offset->find(value)->second + "]\n";
    instruction += "\tmov r6, r7\n";
    instruction += "\tldr r7, [r7]\n";
    instruction += "\tmov lr, pc\n";
    instruction += "\tbx r7\n";
    if (is_returning()) {
      instruction += "\tstr r0, [fp, #" + offset->find(return_variable)->second + "]\n";
    }
    return instruction;
  }

  int arm_closure::nb_regs (void) {
    return 0;
  }

  list<string>* arm_closure::get_op_list (void) {
    list<string>* l = new list<string> ();
    if (is_returning())
      l->push_back(return_variable);
    l->push_back(value);
    for (vector<string>::iterator it = params.begin();
	 it != params.end();
	 it++)
      if (arm_util::type_of (*it) == arm_util::VARIABLE)
	l->push_back(*it);
    l->sort();
    return l;
  }

}
