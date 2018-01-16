#include "asml_factory.h"

namespace asml {

  asml_function* asml_factory::function = NULL;
  vector<asml_function*>* asml_factory::function_list = NULL;
  asml_condition* asml_factory::condition = NULL;
  int asml_factory::next = NORMAL;

  void asml_factory::initialize (void) {
    function = new asml_function ();
    condition = new asml_condition ();
    function_list = new vector<asml_function*> ();
  }

  void asml_factory::validate_function (void) {
    function_list->push_back(function);
    function = NULL;
    function = new asml_function ();
  }

  void asml_factory::validate_condition (void) {
    function->instructions.push_back(condition);
    condition = NULL;
    condition = new asml_condition ();
  }

  asml_instruction* asml_factory::create_instruction (asml_node* node) {
    asml_condition* condition;
    asml_node* current_node;
    if (node->get_type () == asml_node::UNARY)
      return dynamic_cast<asml_unary_node*>(node)->get_instruction();
    else {
      condition = new asml_condition();
      condition->set_var (dynamic_cast<asml_binary_node*>(node)->get_var());
      condition->set_boolean (dynamic_cast<asml_binary_node*>(node)->get_boolean());
      current_node = dynamic_cast<asml_binary_node*>(node)->get_next_true();
      while (current_node != NULL) {
	condition->add_then(create_instruction(current_node));
	current_node = dynamic_cast<asml_unary_node*>(current_node)->get_next();
      }
      current_node = dynamic_cast<asml_binary_node*>(node)->get_next_false();
      while (current_node != NULL) {
	condition->add_else(create_instruction(current_node));
	current_node = dynamic_cast<asml_unary_node*>(current_node)->get_next();
      }
      return condition;
    }
  }

  void asml_factory::add_function (asml_function* fun, asml_node* tree) {
    asml_node* node = tree;
    while (node != NULL) {
      fun->add_instruction(create_instruction(node));
      node = dynamic_cast<asml_unary_node*>(node)->get_next();
    }
    function_list->push_back (fun);
  }

  vector<asml_function*>* asml_factory::get_function (void) {
    return function_list;
  }

  void asml_factory::set_function_name (string name) {
    function->set_name(name);
  }

  void asml_factory::add_int_param (/*vector<*/string/*>**/ name) {
    asml_variable* var;
    /*
    for (vector<string>::iterator it = name->begin();
	 it != name->end();
	 it++) {
      var = new asml_integer ();
      var->set_name (*it);
      function->add_param (var);
    }
    */
    var = new asml_integer();
    var->set_name (name);
    function->add_param (var);
    //delete name;
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
    append (aff);
  }

  void asml_factory::add_funcall (string funcname, string retname,
				  vector<string>* paramlist) {
    asml_funcall* func = new asml_funcall ();
    func->set_funcname (funcname);
    if (*(retname.begin()) != '0')
      func->set_return (retname);
    else
      func->unset_return ();
    for (vector<string>::iterator it = paramlist->begin(); it != paramlist->end(); it++) {
      func->add_param (*it);
    }
    paramlist->erase(paramlist->begin(), paramlist->end());
    delete paramlist;
    append (func);
  }

  void asml_factory::add_addition (string op1, string op2, string op3) {
    asml_addition* addition = new asml_addition ();
    addition->set_op1 (op1);
    addition->set_op2 (op2);
    addition->set_op3 (op3);
    append (addition);
  }

  void asml_factory::add_soustraction (string op1, string op2, string op3) {
    asml_soustraction* soustraction = new asml_soustraction ();
    soustraction->set_op1 (op1);
    soustraction->set_op2 (op2);
    soustraction->set_op3 (op3);
    append (soustraction);
  }

  void asml_factory::set_boolean (string op1, string op2, int type) {
    asml_boolean* boolean = new asml_boolean (type);
    boolean->set_op1 (op1);
    boolean->set_op2 (op2);
    condition->set_boolean(boolean);
  }

  void asml_factory::append (asml_instruction* instr) {
    switch (next) {
    case NORMAL:
      function->add_instruction (instr);
      break;
    case THEN:
      condition->add_then (instr);
      next = NORMAL;
      break;
    case ELSE:
      condition->add_else (instr);
      next = NORMAL;
      break;
    default:
      break;
    }
  }

  void asml_factory::set_next (int next) {
    asml_factory::next = next;
  }

}
