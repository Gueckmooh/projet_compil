#include <string>

#include "asml_instruction.h"

#ifndef __ASML_AFFECTATION_H__
#define __ASML_AFFECTATION_H__

using namespace std;

namespace asml {

  class asml_affectation : public asml_instruction {
  public:
    asml_affectation (void);
    ~asml_affectation (void) {};

    virtual int get_type (void);
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

#endif //__ASML_AFFECTATION_H__
