#include "asml.h"

#ifdef __cplusplus
#include <string>
using namespace std;
#endif //__cplusplus

#ifndef __ASML_FACTORY_H__
#define __ASML_FACTORY_H__

#define ACALL 1
#define AAFFECT 2

typedef struct {
  char* name;
  char* params[32];
  char* vars[32];
  int* vals[32];
  int instr[32];
  char* op[32][32];
  int current_param;
  int current_var;
  int current_instr;
  int current_op;
} asml_factory;

#ifdef __cplusplus
asml_function* create_function (asml_factory* af);
#endif //__cplusplus

#endif
