#include <string>

#ifndef __ASML_MEM_WRITE_H__
#define __ASML_MEM_WRITE_H__

#include "asml_instruction.h"

using namespace std;

namespace asml {

  class asml_mem_write : public asml_instruction {
  public:
    asml_mem_write (void);
    virtual ~asml_mem_write (void) {};

    virtual string generate (int);

    virtual void set_op (string);
    virtual void set_mem_offset (string);
    virtual void set_mem_addr (string);
    virtual void set_value (string);

    virtual string get_op (void);
    virtual string get_mem_offset (void);
    virtual string get_mem_addr (void);
    virtual string get_value (void);
  protected:
    string op;
    string mem_offset;
    string mem_addr;
    string value;
  };

}

#endif //__ASML_MEM_WRITE_H__
