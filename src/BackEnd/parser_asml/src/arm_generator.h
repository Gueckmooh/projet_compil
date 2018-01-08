#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#ifndef __ARM_GENERATOR_H__
#define __ARM_GENERATOR_H__

#include "arm_instruction_factory.h"
#include "arm_function_generator.h"
#include "asml_function.h"
#include "arm_instruction.h"
#include "asml_integer.h"
#include "asml_funcall.h"
#include "arm_funcall.h"
#include "arm_cfg_node.h"
#include "arm_cfg_util.h"
#include "arm_cfg_factory.h"

using namespace std;
using namespace asml;

namespace arm {

  class arm_generator {
  public:
    arm_generator(vector<asml_function*>*);
    ~arm_generator(void);
    void set_name (string);
    void generate (void);
  protected:
    void generate_function (void);
    ofstream* output;
    vector<asml_function*>* asml;
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
    string to_save;

    string name;
    vector<arm_function_generator*> generators;
    vector<arm_instruction*> instructions;
    map<string, string> var_offsets;
  };

}

#endif //__ARM_GENERATOR_H__
