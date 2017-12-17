#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>

#ifndef __ARM_FUNCTION_GENERATOR_H__
#define __ARM_FUNCTION_GENERATOR_H__

#include "arm_instruction_factory.h"
#include "asml_function.h"
#include "arm_instruction.h"
#include "asml_integer.h"
#include "asml_funcall.h"
#include "arm_funcall.h"

using namespace std;
using namespace asml;

namespace arm {

  class arm_function_generator {
  public:
    arm_function_generator (asml_function*);
    ~arm_function_generator (void);
    stringstream* generate (void);
    string get_name (void);
  protected:
    void generate_function (void);
    void pre_process_params (void);
    void process_params (void);
    void pre_process_variables (void);
    void process_instructions (void);
    void pre_process_conditions (void);
    void generate_prologue (void);
    void generate_epilogue (void);
    stringstream* output;
    asml_function* asml;
    int nb_params;
    int nb_variables;
    int sp_offset;
    int fp_offset;
    string prologue;
    string epilogue;
    string processed_params;
    string processed_variables;
    string to_save;
    static int lien;

    string name;
    vector<arm_instruction*> instructions;
    map<string, string> var_offsets;
  };

}

#endif //__ARM_FUNCTION_GENERATOR_H__
