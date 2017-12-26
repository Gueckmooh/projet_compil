#include "asml_closure.h"

namespace asml {

  asml_closure::asml_closure (void) {
    type_id = asml_instruction::CLOSURE;
    do_return = false;
  }

  string asml_closure::get_value (void) {
    return value;
  }

  void asml_closure::set_return (string var) {
    return_variable = var;
    do_return = true;
  }

  void asml_closure::unset_return (void) {
    do_return = false;
  }

  bool asml_closure::is_returning (void) {
    return do_return;
  }

  string asml_closure::get_retval (void) {
    return return_variable;
  }

  void asml_closure::set_value (string name) {
    value = name;
  }

  void asml_closure::add_param (string param) {
    params.push_back(param);
  }

  vector<string>::iterator asml_closure::begin (void) {
    return params.begin();
  }

  vector<string>::iterator asml_closure::end (void) {
    return params.end();
  }

  int asml_closure::size (void) {
    return params.size();
  }

  string asml_closure::operator[] (int t) {
    return params[t];
  }

  string asml_closure::generate (int ident) {
    string ret;
    for (int i = 0; i < ident; i++)
      ret += "\t";
    if (do_return)
      ret += "let " + return_variable + " =";
    ret += "call_closure " + value;
    for (vector<string>::iterator it = params.begin();
	 it != params.end();
	 it++)
      ret += " " + (*it);
    if (do_return)
      ret += " in";
    ret += "\n";
    return ret;
  }


}
