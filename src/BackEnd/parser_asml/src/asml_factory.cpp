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
    var->set_name (name);
    function->add_variable (var);
  }

  void asml_factory::add_int_variable (string name) {
    asml_variable* var = new asml_integer ();
    var->set_name (name);
    function->add_variable (var);
  }

  void asml_factory::add_affectation (string op1, string op2) {
    asml_affectation* aff = new asml_affectation ();
    aff->set_op1 (op1);
    aff->set_op2 (op2);
    function->add_instruction (aff);
  }

  void asml_factory::add_funcall (string funcname, string retname,
				  vector<string>* paramlist) {
    asml_funcall* func = new asml_funcall ();
    func->set_funcname (funcname);
    if (*(retname.begin()) != '0')
      func->set_return (retname);
    else
      func->unset_return ();
    //while (!paramlist->empty()) {
    for (vector<string>::iterator it = paramlist->begin(); it != paramlist->end(); it++) {
      func->add_param (paramlist->front());
      //paramlist->pop_front(); // TODO
    }
    paramlist->erase(paramlist->begin(), paramlist->end());
    delete paramlist;
    function->add_instruction (func);
  }

  void asml_factory::add_addition (string op1, string op2, string op3) {
    asml_addition* addition = new asml_addition ();
    addition->set_op1 (op1);
    addition->set_op2 (op2);
    addition->set_op3 (op3);
    function->add_instruction (addition);
  }

  void asml_factory::add_soustraction (string op1, string op2, string op3) {
    asml_soustraction* soustraction = new asml_soustraction ();
    soustraction->set_op1 (op1);
    soustraction->set_op2 (op2);
    soustraction->set_op3 (op3);
    function->add_instruction (soustraction);
  }

}
