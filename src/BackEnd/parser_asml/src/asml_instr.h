#include <string>
#include <list>
#include <iostream>

#include "asml_op.h"

#ifndef __ASML_INSTR_H__
#define __ASML_INSTR_H__

using namespace std;

class asml_instr {
public:
  static const int AFFECT = 1;
  static const int CALL = 2;

  asml_instr (int);
  ~asml_instr (void);
  void add_arg (asml_op*);
  list<asml_op*>* get_arg_list (void) const;
  void print (void);
protected:
  int type_id;
  list<asml_op*>* args;
};


#endif //__ASML_INSTR_H__
