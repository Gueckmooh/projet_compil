#include "asml_var.h"

template <class T>
asml_var<T>::asml_var(T val, string name) {
  this->val = val;
  this->name = name;
}

template <class T>
void asml_var<T>::set_name (string name) {
  this->name = name;
}

template <class T>
void asml_var<T>::set_val (T val) {
  this->val = val;
}

template <class T>
string asml_var<T>::get_name (void) const {
  return  name;
}

template <class T>
T asml_var<T>::get_val (void) const {
  return this->val;
}

template <class T>
string asml_var<T>::to_string (void) {
  string s = name + " ";
  s+=val;
  return s;
}
