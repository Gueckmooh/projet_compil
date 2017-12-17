#include "asml_condition.h"

namespace asml {

  asml_condition::asml_condition (void) {
    type_id = asml_instruction::CONDITION;
    then_list = new vector<asml_instruction*> ();
    else_list = new vector<asml_instruction*> ();
  }

  asml_condition::~asml_condition (void) {
    delete boolean;
    asml_instruction* instr;
    while (!then_list->empty()) {
      instr = then_list->back();
      then_list->pop_back();
      delete instr;
    }
    while (!else_list->empty()) {
      instr = else_list->back();
      else_list->pop_back();
      delete instr;
    }
    delete then_list;
    delete else_list;
  }

  void asml_condition::set_boolean (asml_boolean* boolean) {
    this->boolean = boolean;
  }

  void asml_condition::add_then (asml_instruction* instr) {
    then_list->push_back(instr);
  }

  void asml_condition::add_else (asml_instruction* instr) {
    else_list->push_back(instr);
  }

  asml_boolean* asml_condition::get_boolean (void) {
    return boolean;
  }

  vector<asml_instruction*>* asml_condition::get_then (void) {
    return then_list;
  }

  vector<asml_instruction*>* asml_condition::get_else (void) {
    return else_list;
  }

}
