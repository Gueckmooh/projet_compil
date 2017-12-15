#include <string>
#include <iostream>

//#include "asml_factory.h"

#ifndef __ASML_INSTRUCTION_H__
#define __ASML_INSTRUCTION_H__

using namespace std;

namespace asml {

  class asml_instruction {
    friend class asml_factory;
  public:
    static const int FUNCALL = 1;
    static const int AFFECTATION = 2;

    virtual ~asml_instruction (void) {};

    virtual int get_type (void);
    //virtual void print (void) = 0;
  protected:
    int type_id;
  };

}

#endif //__ASML_INSTRUCTION_H__
