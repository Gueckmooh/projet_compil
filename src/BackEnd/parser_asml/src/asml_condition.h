#include <vector>
#include <string>

#ifndef __ASML_IF_H__
#define __ASML_IF_H__

#include "asml_instruction.h"
#include "asml_boolean.h"

using namespace std;

namespace asml {

  class asml_condition : public asml_instruction {
  public:
    asml_condition (void);
    ~asml_condition (void);

    virtual void set_boolean (asml_boolean*);
    virtual void add_then (asml_instruction*);
    virtual void add_else (asml_instruction*);

    virtual asml_boolean* get_boolean (void);
    virtual vector<asml_instruction*>* get_then (void);
    virtual vector<asml_instruction*>* get_else (void);
  protected:
    asml_boolean* boolean;
    vector<asml_instruction*>* then_list;
    vector<asml_instruction*>* else_list;
  };
}

#endif //__ASML_IF_H__
