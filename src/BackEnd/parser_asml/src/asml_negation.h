#include <string>
#include <iostream>

#ifndef __ASML_NEGATION_H__
#define __ASML_NEGATION_H__

#include "asml_instruction.h"

using namespace std;

namespace asml {

  class asml_negation : public asml_instruction {
  public:
    asml_negation (void);
    ~asml_negation (void) {};

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);

    virtual string generate (int);
  protected:
    string op1;
    string op2;
  };

}

#endif //__ASML_NEGATION_H__
