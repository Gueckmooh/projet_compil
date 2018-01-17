#include "asml_factory.h"

namespace asml {

  asml_function* asml_factory::function = NULL;
  vector<asml_function*>* asml_factory::function_list = NULL;
  asml_condition* asml_factory::condition = NULL;
  int asml_factory::next = NORMAL;

  void asml_factory::initialize (void) {
    function_list = new vector<asml_function*> ();
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

}
