#include "asml_function.h"
#include "arm_instruction.h"
#include <string>
#include <list>
#include <iostream>
#include <fstream>

using namespace std;

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
    ofstream* output;
    asml_function* asml;
    string filename;

    string name;
    list<arm_instruction*> instructions;
  };

}

#endif //__ARM_GENERATOR_H__
