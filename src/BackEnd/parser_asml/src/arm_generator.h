#include "asml.h"
#include <string>
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
    string name;
  };

}

#endif //__ARM_GENERATOR_H__
