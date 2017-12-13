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
  void add_param (asml_var*);
  void add_var (asml_var*);
  void add_instr (asml_instr*);
  asml_var* get_param (string);
  asml_var* get_var (string);
  //asml_instr* get_instr (int);
  void print (void);
protected:
  string name;
  list<asml_var*>* vars;
  list<asml_var*>* params;
  list<asml_instr*>* instructions;
};

#endif //__ASML_FUNCTONS_H__
