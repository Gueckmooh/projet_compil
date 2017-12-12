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
void asml_var<T>::set_init_val (T val) {
  this->val = val;
}

template <class T>
T asml_var<T>::get_init_val (void) const {
  return this->val;
}
