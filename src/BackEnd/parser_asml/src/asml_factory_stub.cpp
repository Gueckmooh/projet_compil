#include "asml_factory_stub.h"

/*
extern "C" void asml_create_function (void) {
  asml_factory::create_function();
}
*/

extern "C" void asml_validate_function (void) {
  asml_factory::validate_function();
}

extern "C" void asml_validate_condition (void) {
  asml_factory::validate_condition();
}

extern "C" void asml_set_function_name (char* name) {
  asml_factory::set_function_name(string(name));
}

extern "C" void asml_add_int_param (char* params) {
  string name = string(params);
  asml_factory::add_int_param (name);
}

extern "C" void asml_add_int_variable (char* param) {
  asml_factory::add_int_variable (string(param));
}

extern "C" void asml_add_affectation (char* op1, char* op2) {
  asml_factory::add_affectation (string(op1), string(op2));
}

extern "C" void asml_add_funcall (char* funcname, char* retval, char* params) {
  vector<string>* vect = new vector<string> ();
  char* current = params;
  if (params != NULL) {
    while (*current != '\0') {
      if (*current == ' ')
	*current = '\0';
      current++;
    }
    current = params;
    while (strlen(current) != 0) {
      vect->push_back(string(current));
      current += strlen (current)+1;
    }
  }
  asml_factory::add_funcall (string(funcname), string(retval), vect);
  free (params);
}

extern "C" void asml_add_addition (char* op1, char* op2, char* op3) {
  asml_factory::add_addition (string(op1), string(op2), string(op3));
}

extern "C" void asml_add_soustraction (char* op1, char* op2, char* op3) {
  asml_factory::add_soustraction (string(op1), string(op2), string(op3));
}

extern "C" void asml_set_boolean (char* op1, char* op2, int type) {
  switch (type) {
  case ASML_LT:
    asml_factory::set_boolean (string(op1), string(op2), asml_boolean::LT);
    break;
  case ASML_GT:
    asml_factory::set_boolean (string(op1), string(op2), asml_boolean::GT);
    break;
  case ASML_LE:
    asml_factory::set_boolean (string(op1), string(op2), asml_boolean::LE);
    break;
  case ASML_GE:
    asml_factory::set_boolean (string(op1), string(op2), asml_boolean::GE);
    break;
  case ASML_EQUAL:
    asml_factory::set_boolean (string(op1), string(op2), asml_boolean::EQUAL);
    break;
  default:
    break;
  }
}

extern "C" void asml_set_next (int next) {
  switch (next) {
  case ASML_NORMAL:
    asml_factory::set_next(asml_factory::NORMAL);
    break;
  case ASML_THEN:
    asml_factory::set_next(asml_factory::THEN);
    break;
  case ASML_ELSE:
    asml_factory::set_next(asml_factory::ELSE);
    break;
  }
}
