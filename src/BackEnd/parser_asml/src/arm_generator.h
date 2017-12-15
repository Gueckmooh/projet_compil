#include "asml_function.h"
#include "arm_instruction.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
using namespace asml;

#ifndef __ARM_GENERATOR_H__
#define __ARM_GENERATOR_H__

namespace arm {

  class arm_generator {
  public:
    arm_generator(asml_function*);
    ~arm_generator(void);
    void set_name (string);
    void generate (void);
  protected:
    void pre_process_params (void);
    void process_params (void);
    void pre_process_variables (void);
    void process_variables (void);
    void pre_process_instructions (void);
    void process_instructions (void);
    void generate_prologue (void);
    void generate_epilogue (void);
    ofstream* output;
    asml_function* asml;
    string filename;
    int nb_params;
    int nb_variables;
    int sp_offset;
    int fp_offset;
    bool do_save_sp;
    string prologue;
    string epilogue;
    string processed_params;
    string processed_variables;

    string name;
    vector<arm_instruction*> instructions;
    map<string, string> var_offsets;
  };

}

#endif //__ARM_GENERATOR_H__
