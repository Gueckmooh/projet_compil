#include <iostream>
#include <string>
#include <list>

#include "asml_var.h"
#include "asml_instr.h"

using namespace std;

#ifndef __ASML_FUNCTONS_H__
#define __ASML_FUNCTONS_H__

class asml_function {
public:
  asml_function (string);
  ~asml_function (void);
  void add_param (asml_var<int>*);
  void add_var (asml_var<int>*);
  asml_var<int>* get_param (string);
  asml_var<int>* get_var (string);
  void print (void);
protected:
  string name;
  list<asml_var<int>*>* vars;
  list<asml_var<int>*>* params;
  list<asml_instr*>* instructions;
};

#endif //__ASML_FUNCTONS_H__
