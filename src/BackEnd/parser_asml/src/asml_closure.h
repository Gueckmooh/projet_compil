#include <string>
#include <vector>

#include "asml_instruction.h"

#ifndef __ASML_CLOSURE_H__
#define __ASML_CLOSURE_H__

using namespace std;

namespace asml {

  class asml_closure : public asml_instruction {
  public:
    asml_closure (void);
    ~asml_closure (void) {};

    virtual string get_value (void);

    virtual void set_value (string);
    virtual void set_return (string);
    virtual void unset_return (void);
    virtual bool is_returning (void);
    virtual string get_retval (void);
    virtual void add_param (string);
    virtual vector<string>::iterator begin (void);
    virtual vector<string>::iterator end (void);
    virtual int size (void);
    virtual string operator[] (int);
    virtual string generate (int);
  protected:
    string value;
    string return_variable;
    bool do_return;
    vector<string> params;
  };

}

#endif //__ASML_CLOSURE_H__
