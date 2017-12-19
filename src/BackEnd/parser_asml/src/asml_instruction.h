#include <string>
#include <iostream>

#ifndef __ASML_INSTRUCTION_H__
#define __ASML_INSTRUCTION_H__

using namespace std;

namespace asml {

  class asml_instruction {
    friend class asml_factory;
  public:
    static const int FUNCALL = 1;
    static const int AFFECTATION = 2;
    static const int ADDITION = 3;
    static const int SOUSTRACTION = 4;
    static const int CONDITION = 5;
    static const int NEGATION = 6;

    virtual ~asml_instruction (void) {};

    virtual int get_type (void);
    //virtual void print (void) = 0;
  protected:
    int type_id;
  };

}

#endif //__ASML_INSTRUCTION_H__
