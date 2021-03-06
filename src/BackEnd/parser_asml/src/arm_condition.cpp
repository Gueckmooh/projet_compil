#include "arm_condition.h"


namespace arm {

  arm_condition::arm_condition (void) {
    list_then = new vector<arm_instruction*> ();
    list_else = new vector<arm_instruction*> ();
    type_id = arm_instruction::CONDITION;
  }

  arm_condition::~arm_condition (void) {
    arm_instruction* instr;
    while (!list_then->empty()) {
      instr = list_then->back();
      list_then->pop_back();
      delete instr;
    }
    while (!list_else->empty()) {
      instr = list_else->back();
      list_else->pop_back();
      delete instr;
    }
    delete list_then;
    delete list_else;
    delete boolean;
  }

  void arm_condition::set_var_offset (map<string, string>* map) {
    this->offset = map;
    this->boolean->offset = map;
    for (vector<arm_instruction*>::iterator it = list_then->begin();
	 it != list_then->end();
	 it++)
      (*it)->set_var_offset(map);
    for (vector<arm_instruction*>::iterator it = list_else->begin();
	 it != list_else->end();
	 it++)
      (*it)->set_var_offset(map);
  }

  string arm_condition::get_instruction (void) {
    stringstream ss;
    ss << boolean->get_instruction();
    for (vector<arm_instruction*>::iterator it = list_then->begin();
	 it != list_then->end();
	 it++) {
      ss << (*it)->get_instruction();
    }
    ss << "\tb " << lFin << "\n";
    ss << lFalse << ":\n";
    for (vector<arm_instruction*>::iterator it = list_else->begin();
	 it != list_else->end();
	 it++) {
      ss << (*it)->get_instruction();
    }
    ss << lFin << ":\n";
    if (var.compare("0") != 0) {
      ss << "\tstr r0, [fp, #"+ offset->find(var)->second + "]\n";
    }
    return ss.str();
  }

  void arm_condition::set_var (string var) {
    this->var = var;
  }

  void arm_condition::add_then (arm_instruction* instr) {
    list_then->push_back(instr);
  }

  void arm_condition::add_else (arm_instruction* instr) {
    list_else->push_back(instr);
  }

  void arm_condition::set_boolean (arm_boolean* boolean) {
    this->boolean = boolean;
  }

  void arm_condition::set_lFalse (string l) {
    lFalse = l;
    boolean->set_lFalse (l);
    boolean->offset = offset;
  }

  void arm_condition::set_lFin (string l) {
    lFin = l;
  }

  int arm_condition::nb_regs (void) {
    return boolean->nb_regs();
  }

  list<string>* arm_condition::get_op_list (void) {
    list<string>* l = new list<string> ();
    list<string>* l2;
    if (var.compare("0") != 0)
      l->push_back(var);
    l2 = boolean->get_op_list();
    l->merge(*l2);
    delete l2;
    l->sort();
    return l;
  }

  vector<arm_instruction*>* arm_condition::get_list_then (void) {
    return list_then;
  }

  vector<arm_instruction*>* arm_condition::get_list_else (void) {
    return list_else;
  }

}
