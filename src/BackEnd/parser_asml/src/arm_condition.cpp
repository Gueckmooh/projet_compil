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

  string arm_condition::get_instruction (void) {
    stringstream ss;
    ss << boolean->get_instruction();
    for (vector<arm_instruction*>::iterator it = list_then->begin();
	 it != list_then->end();
	 it++) {
      ss << (*it)->get_instruction();
    }
    ss << lFalse << ":\n";
    for (vector<arm_instruction*>::iterator it = list_else->begin();
	 it != list_else->end();
	 it++) {
      ss << (*it)->get_instruction();
    }
    ss << lFin << ":\n";
    return ss.str();
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
  }

  void arm_condition::set_lFin (string l) {
    lFin = l;
  }

}
