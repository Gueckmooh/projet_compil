#include <iostream>
#include <string>
#include <vector>

#include "asml_variable.h"
#include "asml_instruction.h"

#ifndef __ASML_FUNCTON_H__
#define __ASML_FUNCTON_H__

using namespace std;

namespace asml {

  class asml_function {
    friend class asml_factory;
  public:
    ~asml_function (void);

    virtual void set_name (string);
    virtual void add_param (asml_variable*);
    virtual void add_variable (asml_variable*);
    virtual void add_instruction (asml_instruction*);

    virtual string get_name (void);
    virtual vector<asml_variable*>::iterator variable_begin (void);
    virtual vector<asml_variable*>::iterator variable_end (void);
    virtual vector<asml_variable*>::iterator param_begin (void);
    virtual vector<asml_variable*>::iterator param_end (void);
    virtual vector<asml_instruction*>::iterator instruction_begin (void);
    virtual vector<asml_instruction*>::iterator instruction_end (void);
    virtual vector<asml_variable*>* get_variables (void);
    virtual vector<asml_variable*>* get_params (void);
    virtual vector<asml_instruction*>* get_instructions (void);

    virtual string generate (void);
  protected:
    string name;
    vector<asml_variable*> variables;
    vector<asml_variable*> params;
    vector<asml_instruction*> instructions;
  };

}

#endif //__ASML_FUNCTON_H__
