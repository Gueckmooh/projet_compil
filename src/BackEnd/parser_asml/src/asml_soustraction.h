#include <string>
#include <iostream>

#ifndef __ASML_SOUSTRACTION_H__
#define __ASML_SOUSTRACTION_H__

#include "asml_instruction.h"

using namespace std;

namespace asml {

  class asml_soustraction : public asml_instruction {
  public:
    asml_soustraction (void);
    ~asml_soustraction (void) {};

    virtual string get_op1 (void);
    virtual string get_op2 (void);
    virtual string get_op3 (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_op3 (string);

    virtual string generate (int);
  protected:
    string op1;
    string op2;
    string op3;
  };

}

#endif //__ASML_SOUSTRACTION_H__
