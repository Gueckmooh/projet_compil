#include "asml_parser_driver.h"

extern "C" void asml_parser_create_function (char* name, asml_formal_arg_t* args, asml_asmt_t* asmt) {
  asml_function* function = new asml_function();
  asml_variable* var;
  asml_node* tree;
  asml_formal_arg_t* current_arg = args;
  asml_asmt_t* current_asmt = asmt;
  function->set_name(string(name));
  while (current_arg != NULL) {
    var = new asml_integer();
    var->set_name (string(current_arg->val));
    function->add_param (var);
    current_arg = current_arg->next;
  }
  while (current_asmt != NULL) {
    if (current_asmt->op != NULL) {
      var = new asml_integer ();
      var->set_name (string(current_asmt->op));
      function->add_variable (var);
    }
    current_asmt = current_asmt->next;
  }
  tree = asml_parser_create_tree (asmt);
  asml_factory::add_function (function, tree);
}

asml_node* asml_parser_create_tree (asml_asmt_t* asmt) {
  asml_boolean* boolean;
  asml_instruction* instruction;
  asml_node* node = NULL;
  if (asmt == NULL)
    return NULL;
  switch (asmt->exp->type) {
  case ASML_EXP_INT    :
    node = new asml_unary_node ();
    instruction = new asml_affectation ();
    dynamic_cast<asml_affectation*>(instruction)->set_op1 (string(asmt->op));
    dynamic_cast<asml_affectation*>(instruction)->set_op2 (string((char*)asmt->exp->op1));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  case ASML_EXP_IDENT  :
    node = new asml_unary_node ();
    instruction = new asml_affectation ();
    dynamic_cast<asml_affectation*>(instruction)->set_op1 (string(asmt->op));
    dynamic_cast<asml_affectation*>(instruction)->set_op2 (string((char*)asmt->exp->op1));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  case ASML_EXP_LABEL  :
    node = new asml_unary_node ();
    instruction = new asml_affectation ();
    dynamic_cast<asml_affectation*>(instruction)->set_op1 (string(asmt->op));
    dynamic_cast<asml_affectation*>(instruction)->set_op2 (string((char*)asmt->exp->op1));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  case ASML_EXP_ADD    :
    node = new asml_unary_node ();
    instruction = new asml_addition ();
    dynamic_cast<asml_addition*>(instruction)->set_op1 (string((asmt->op == NULL ? "0" : (char*)asmt->op)));
    dynamic_cast<asml_addition*>(instruction)->set_op2 (string((char*)asmt->exp->op1));
    dynamic_cast<asml_addition*>(instruction)->set_op3 (string((char*)asmt->exp->op2));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  case ASML_EXP_SUB    :
    node = new asml_unary_node ();
    instruction = new asml_soustraction ();
    dynamic_cast<asml_soustraction*>(instruction)->set_op1 (string((asmt->op == NULL ? "0" : (char*)asmt->op)));
    dynamic_cast<asml_soustraction*>(instruction)->set_op2 (string((char*)asmt->exp->op1));
    dynamic_cast<asml_soustraction*>(instruction)->set_op3 (string((char*)asmt->exp->op2));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  case ASML_EXP_IF     :
    node = new asml_binary_node ();
    boolean = asml_parser_create_boolean ((asml_exp_t*)asmt->exp->op1);
    dynamic_cast<asml_binary_node*>(node)->set_next_true(asml_parser_create_tree ((asml_asmt_t*)asmt->exp->op2));
    dynamic_cast<asml_binary_node*>(node)->set_next_false(asml_parser_create_tree ((asml_asmt_t*)asmt->exp->op3));
    dynamic_cast<asml_binary_node*>(node)->set_boolean(boolean);
    break;
  case ASML_EXP_CALL   :
    node = new asml_unary_node ();
    instruction = new asml_funcall ();
    dynamic_cast<asml_funcall*>(instruction)->set_funcname (string((char*)asmt->exp->op1));
    if (asmt->op != NULL)
      dynamic_cast<asml_funcall*>(instruction)->set_return (asmt->op);
    asml_parser_set_params ((asml_formal_arg_t*)asmt->exp->op2, dynamic_cast<asml_funcall*>(instruction));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  case ASML_EXP_NEG    :
    node = new asml_unary_node ();
    instruction = new asml_negation ();
    dynamic_cast<asml_negation*>(instruction)->set_op1 (string((asmt->op == NULL ? "0" : (char*)asmt->op)));
    dynamic_cast<asml_negation*>(instruction)->set_op2 (string((char*)asmt->exp->op1));
    dynamic_cast<asml_unary_node*>(node)->set_instruction (instruction);
    break;
  }
  dynamic_cast<asml_unary_node*>(node)->set_next(asml_parser_create_tree(asmt->next));
  return node;
}

asml_boolean* asml_parser_create_boolean (asml_exp_t* boolean) {
  asml_boolean* ret;
  int type = -1;
  switch (boolean->type) {
  case ASML_COND_EQUAL :
    type = asml_boolean::EQUAL;
    break;
  case ASML_COND_LE    :
    type = asml_boolean::LE;
    break;
  case ASML_COND_GE    :
    type = asml_boolean::GE;
    break;
  }
  ret = new asml_boolean(type);
  ret->set_op1(string((char*)boolean->op1));
  ret->set_op2(string((char*)boolean->op2));
  return ret;
}

void asml_parser_set_params (asml_formal_arg_t* args, asml_funcall* funcall) {
  while (args != NULL) {
    funcall->add_param (string(args->val));
    args = args->next;
  }
}

extern "C" asml_asmt_t* asml_parser_add_asmt (char* op, asml_exp_t* exp, asml_asmt_t* next) {
  asml_asmt_t* asmt = (asml_asmt_t*) malloc (sizeof (asml_asmt_t));
  asmt->next = next;
  asmt->exp = exp;
  asmt->op = op;
  return asmt;
}

extern "C" asml_exp_t* asml_parser_create_exp (int type, void* op1, void* op2, void* op3) {
  asml_exp_t* exp = (asml_exp_t*) malloc (sizeof (asml_exp_t));
  exp->type = type;
  exp->op1 = op1;
  exp->op2 = op2;
  exp->op3 = op3;
  return exp;
}

extern "C" asml_formal_arg_t* asml_parser_add_arg (char* op, asml_formal_arg_t* next) {
  asml_formal_arg_t* args = (asml_formal_arg_t*) malloc (sizeof(asml_formal_arg_t));
  args->val = op;
  args->next = next;
  return args;
}
