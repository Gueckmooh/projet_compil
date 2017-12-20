#include "asml_function.h"

namespace asml {

  asml_function::~asml_function (void) {
    asml_variable* var;
    asml_instruction* instr;
    while (!variables.empty()) {
      var = variables.back();
      variables.pop_back();
      delete var;
    }
    while (!params.empty()) {
      var = params.back();
      params.pop_back();
      delete var;
    }
    while (!instructions.empty()) {
      instr = instructions.back();
      instructions.pop_back();
      delete instr;
    }
  }

  void asml_function::set_name (string name) {
    this->name = name;
  }

  void asml_function::add_param (asml_variable* param) {
    params.push_back(param);
  }

  void asml_function::add_variable (asml_variable* var) {
    variables.push_back(var);
  }

  void asml_function::add_instruction (asml_instruction* instr) {
    instructions.push_back(instr);
  }

  string asml_function::get_name (void) {
    return name;
  }

  vector<asml_variable*>::iterator asml_function::variable_begin (void) {
    return variables.begin();
  }

  vector<asml_variable*>::iterator asml_function::variable_end (void) {
    return  variables.end();
  }

  vector<asml_variable*>::iterator asml_function::param_begin (void) {
    return params.begin();
  }

  vector<asml_variable*>::iterator asml_function::param_end (void) {
    return params.end();
  }

  vector<asml_instruction*>::iterator asml_function::instruction_begin (void) {
    return instructions.begin();
  }

  vector<asml_instruction*>::iterator asml_function::instruction_end (void) {
    return instructions.end();
  }

  vector<asml_variable*>* asml_function::get_variables (void) {
    return &variables;
  }

  vector<asml_variable*>* asml_function::get_params (void) {
    return &params;
  }

  vector<asml_instruction*>* asml_function::get_instructions (void) {
    return &instructions;
  }

  string asml_function::generate (void) {
    string ret;
    ret += "let " + (name.compare("main") == 0 ? "_" : name);
    for (vector<asml_variable*>::iterator it = params.begin();
	 it != params.end();
	 it++) {
      ret += " " + (*it)->get_name();
    }
    ret += " =\n";
    for (vector<asml_instruction*>::iterator it = instructions.begin();
	 it != instructions.end();
	 it++) {
      ret += (*it)->generate(1);
    }
    return ret;
  }

}
