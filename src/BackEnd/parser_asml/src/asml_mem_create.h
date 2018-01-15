#include <string>

#ifndef __ASML_MEM_CREATE_H__
#define __ASML_MEM_CREATE_H__

#include "asml_instruction.h"

using namespace std;

namespace asml {

  class asml_mem_create : public asml_instruction {
  public:
    asml_mem_create (void);
    virtual ~asml_mem_create (void) {};

    virtual string generate (int);

    virtual void set_op (string);
    virtual void set_size (string);

    virtual string get_op (void);
    virtual string get_size (void);
  protected:
    string op;
    string size;
  };

} // TODO

#endif //__ASML_MEM_CREATE_H__
