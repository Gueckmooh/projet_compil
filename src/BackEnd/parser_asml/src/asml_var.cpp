#include "asml_var.h"

asml_var::asml_var(int val, string name) {
  this->val = val;
  this->name = name;
}

void asml_var::set_name (string name) {
  this->name = name;
}

void asml_var::set_val (int val) {
  this->val = val;
}

string asml_var::get_name (void) const {
  return  name;
}

int asml_var::get_val (void) const {
  return this->val;
}

string asml_var::to_string (void) {
  string s = name + " ";
  s+=val;
  return s;
}
