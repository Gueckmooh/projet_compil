#include "asml_funcall.h"

namespace asml {

  asml_funcall::asml_funcall (void) {
    type_id = asml_instruction::FUNCALL;
    do_return = false;
  }

  string asml_funcall::get_funcname (void) {
    return funcname;
  }

  void asml_funcall::set_return (string var) {
    return_variable = var;
    do_return = true;
  }

  void asml_funcall::unset_return (void) {
    do_return = false;
  }

  bool asml_funcall::is_returning (void) {
    return do_return;
  }

  string asml_funcall::get_retval (void) {
    return return_variable;
  }

  void asml_funcall::set_funcname (string name) {
    funcname = name;
  }

  void asml_funcall::add_param (string param) {
    params.push_back(param);
  }

  vector<string>::iterator asml_funcall::begin (void) {
    return params.begin();
  }

  vector<string>::iterator asml_funcall::end (void) {
    return params.end();
  }

  int asml_funcall::size (void) {
    return params.size();
  }

  string asml_funcall::operator[] (int t) {
    return params[t];
  }

}
