#include <string>
#include <vector>

#include "asml_instruction.h"

#ifndef __ASML_FUNCALL_H__
#define __ASML_FUNCALL_H__

using namespace std;

namespace asml {

  class asml_funcall : public asml_instruction {
  public:
    asml_funcall (void);
    ~asml_funcall (void) {};

    virtual string get_funcname (void);

    virtual void set_funcname (string);
    virtual void set_return (string);
    virtual void unset_return (void);
    virtual bool is_returning (void);
    virtual string get_retval (void);
    virtual void add_param (string);
    virtual vector<string>::iterator begin (void);
    virtual vector<string>::iterator end (void);
    virtual int size (void);
    virtual string operator[] (int);
    //virtual void print (void);
  protected:
    string funcname;
    string return_variable;
    bool do_return;
    vector<string> params;
  };

}

#endif //__ASML_FUNCALL_H__
