#include "asml_function.h"

asml_function::asml_function (string name) {
  this->name = name;
  vars = new list<asml_var*> ();
  params = new list<asml_var*> ();
  instructions = new list<asml_instr*> ();
}

asml_function::~asml_function (void) {
  asml_var* var;
  asml_instr* instr;
  while (!vars->empty()) {
    var = vars->back();
    delete var;
    vars->pop_back();
  }
  while (!params->empty()) {
    var = params->back();
    delete var;
    params->pop_back();
  }
  while (!params->empty()) {
    instr = instructions->back();
    delete instr;
    instructions->pop_back();
  }
  delete vars;
  delete params;
  delete instructions;
}

void asml_function::add_param (asml_var* param) {
  params->push_back(param);
}

void asml_function::add_var (asml_var* var) {
  vars->push_back(var);
}

asml_var* asml_function::get_param (string name) {
  for (list<asml_var*>::iterator it = params->begin(); it != params->end(); it++) {
    if (!(((*it)->get_name()).compare(name))) {
      (*it)->get_val();
      return *it;
    }
  }
  return NULL;
}

asml_var* asml_function::get_var (string) {
  for (list<asml_var*>::iterator it = vars->begin(); it != vars->end(); it++) {
    if (!((*it)->get_name().compare(name)))
      return *it;
  }
  return NULL;
}
void asml_function::print (void) {
  cout << "function " << name << " ";
  for (list<asml_var*>::iterator it = params->begin(); it != params->end(); it++)
    cout << (*it)->to_string() << " ";
  cout << endl;
  cout << "Variables : ";
  for (list<asml_var*>::iterator it = vars->begin(); it != vars->end(); it++)
    cout << (*it)->to_string() << " ";
  cout << endl;
  for (list<asml_instr*>::iterator it = instructions->begin(); it != instructions->end(); it++)
    (*it)->print();
}
