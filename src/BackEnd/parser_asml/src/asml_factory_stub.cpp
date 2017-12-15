#include "asml_factory_stub.h"

extern "C" void asml_create_function (void) {
  asml_factory::create_function();
}

extern "C" void asml_set_function_name (char* name) {
  asml_factory::set_function_name(string(name));
}

extern "C" void asml_add_int_param (char* var) {
  asml_factory::add_int_param (string(var));
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
  while (*current != '\0') {
    if (*current == ' ')
      *current = '\0';
    current++;
  }
  current = params;
  while (strlen(current) != 0) {
    vect->push_back(string(params));
    current += strlen (current)+1;
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
