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

  void asml_condition::set_var (string var) {
    this->var = var;
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

  string asml_condition::get_var (void) {
    return var;
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

  string asml_condition::generate (int indent) {
    string ret;
    for (int i = 0; i < indent; i++)
      ret += "\t";
    if (var.compare("0") != 0)
      ret += "let " + var + " = ";
    ret += "if " + boolean->generate() + " then (\n";
    for (vector<asml_instruction*>::iterator it = then_list->begin();
	 it != then_list->end();
	 it++) {
      ret += (*it)->generate(indent+1);
    }
    for (int i = 0; i < indent; i++)
      ret += "\t";
    ret += ") else (\n";
    for (vector<asml_instruction*>::iterator it = else_list->begin();
	 it != else_list->end();
	 it++) {
      ret += (*it)->generate(indent+1);
    }
    for (int i = 0; i < indent; i++)
      ret += "\t";
    ret += ")";
    if (var.compare("0") != 0)
      ret += " in";
    ret += "\n";
    return ret;
  }

}
