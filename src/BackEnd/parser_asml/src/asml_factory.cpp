#include "asml_factory.h"

namespace asml {

  asml_function* asml_factory::function = NULL;

  void asml_factory::create_function (void) {
    function = new asml_function ();
  }

  asml_function* asml_factory::get_function (void) {
    return function;
  }

  void asml_factory::set_function_name (string name) {
    function->set_name(name);
  }

  void asml_factory::add_int_param (string name) {
    asml_variable* var = new asml_integer ();
    dynamic_cast<asml_integer*>(var)->unset_value ();
    var->set_name (name);
    function->add_variable (var);
  }

  void asml_factory::add_int_variable (string name, int value) {
    asml_variable* var = new asml_integer ();
    dynamic_cast<asml_integer*>(var)->set_value (value);
    var->set_name (name);
    function->add_variable (var);
  }

  void asml_factory::add_affectation (string op1, string op2) {
    asml_instruction* aff = new asml_affectation ();
    dynamic_cast<asml_affectation*>(aff)->set_op1 (op1);
    dynamic_cast<asml_affectation*>(aff)->set_op2 (op2);
    function->add_instruction (aff);
  }

  void asml_factory::add_funcall (string funcname, string retname,
				  vector<string>* paramlist) {
    asml_instruction* func = new asml_funcall ();
    dynamic_cast<asml_funcall*>(func)->set_funcname (funcname);
    if (*(retname.begin()) != '0')
      dynamic_cast<asml_funcall*>(func)->set_return (retname);
    else
      dynamic_cast<asml_funcall*>(func)->unset_return ();
    //while (!paramlist->empty()) {
    for (vector<string>::iterator it = paramlist->begin(); it != paramlist->end(); it++) {
      dynamic_cast<asml_funcall*>(func)->add_param (paramlist->front());
      //paramlist->pop_front(); // TODO
    }
    paramlist->erase(paramlist->begin(), paramlist->end());
    delete paramlist;
    function->add_instruction (func);
  }

}
