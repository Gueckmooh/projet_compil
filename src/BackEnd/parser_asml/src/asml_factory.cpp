#include "asml_factory.h"

namespace asml {

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
    var->unset_value ();
    var->set_name (name);
    function->add_variable (var);
  }

  void asml_factory::add_int_variable (string name, int value) {
    asml_variable* var = new asml_integer ();
    var->set_value (value);
    var->set_name (name);
    function->add_variable (var);
  }

  void asml_factory::add_affectation (string op1, string op2) {
    asml_instruction* aff = new asml_affectation ();
    aff->set_op1 (op1);
    aff->set_op2 (op2);
    function->add_instruction (aff);
  }

  void asml_factory::add_funcall (string funcname, string retname,
				  vector<string>* paramlist) {
    asml_instruction* func = new asml_funcall ();
    func->get_funcname (funcname);
    if (*(retname.head()) != '0')
      func->set_return (retname);
    else
      func->unset_return ();
    while (!paramlist->empty()) {
      func->add_param (*(paramlist->front()));
      paramlist->pop_front();
    }
    delete vector;
    function->add_instruction (func);
  }

}
