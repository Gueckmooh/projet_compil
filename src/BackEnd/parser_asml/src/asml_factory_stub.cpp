#include "asml_factory_stub.h"

extern "C" void asml_create_function (void) {
  asml_factory::create_function();
}

extern "C" void asml_set_function_name (char* name) {
  asml_factory::set_function_name(string(name));
}

extern "C" void asml_add_int_variable (char* var) {
  asml_factory::add_int_variable (string(var));
}

extern "C" void asml_add_int_param (char* param, int value) {
  asml_factory::add_int_param (string(param), value);
}

extern "C" void asml_add_affectation (char* op1, char* op2) {
  asml_factory::add_affectation (string(op1), string(op2));
}

extern "C" void asml_add_funcall (char* funcname, char* retval, char* params) {
  vector<string>* vect = new vector<string> ();
  char* current = c;
  while (*current != '\0') {
    if (*current == ' ')
      *current = '\0';
    current++;
  }
  current = params;
  while (strlen(current) != 0) {
    vector->push_back(string(params));
    current += strlen (current)+1;
  }
  asml_factory::add_funcall (string(funcname), string(retval), vect);
  free (params);
}
