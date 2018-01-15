#include <string>

#ifndef __ASML_MEM_READ_H__
#define __ASML_MEM_READ_H__

#include "asml_instruction.h"

using namespace std;

namespace asml {

  class asml_mem_read : public asml_instruction {
  public:
    asml_mem_read (void);;
    virtual ~asml_mem_read (void) {};

    virtual string generate (int);

    virtual void set_op (string);
    virtual void set_mem_offset (string);
    virtual void set_mem_addr (string);

    virtual string get_op (void);
    virtual string get_mem_offset (void);
    virtual string get_mem_addr (void);
  protected:
    string op;
    string mem_offset;
    string mem_addr;
  };

} // TODO

#endif //__ASML_MEM_READ_H__
