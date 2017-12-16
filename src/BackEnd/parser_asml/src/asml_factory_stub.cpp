#include "asml_factory_stub.h"

/*
extern "C" void asml_create_function (void) {
  asml_factory::create_function();
}
*/

extern "C" void asml_validate_function (void) {
  asml_factory::validate_function();
}

extern "C" void asml_set_function_name (char* name) {
  asml_factory::set_function_name(string(name));
}

extern "C" void asml_add_int_param (char* params) {
  vector<string>* vect = new vector<string> ();
  char* current = params;
  cout << string(params) << endl;
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
  asml_factory::add_int_param (vect);
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
  cout << string(params) << endl;
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
  asml_factory::add_funcall (string(funcname), string(retval), vect);
  free (params);
}

extern "C" void asml_add_addition (char* op1, char* op2, char* op3) {
  asml_factory::add_addition (string(op1), string(op2), string(op3));
}

extern "C" void asml_add_soustraction (char* op1, char* op2, char* op3) {
  asml_factory::add_soustraction (string(op1), string(op2), string(op3));
}
