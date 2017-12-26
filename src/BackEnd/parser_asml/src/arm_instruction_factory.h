#include <iostream>
#include <string>
#include <map>
#include <vector>

#ifndef __ARM_INSTRUCTION_FACTORY_H__
#define __ARM_INSTRUCTION_FACTORY_H__

#include "asml_instruction.h"
#include "asml_funcall.h"
#include "asml_affectation.h"
#include "asml_addition.h"
#include "asml_soustraction.h"
#include "asml_condition.h"
#include "asml_negation.h"
#include "asml_mem_create.h"
#include "asml_mem_read.h"
#include "asml_mem_write.h"
#include "asml_closure.h"
#include "arm_instruction.h"
#include "arm_funcall.h"
#include "arm_affectation.h"
#include "arm_addition.h"
#include "arm_soustraction.h"
#include "arm_condition.h"
#include "arm_negation.h"
#include "arm_mem_create.h"
#include "arm_mem_read.h"
#include "arm_mem_write.h"
#include "arm_closure.h"

using namespace std;
using namespace asml;

namespace arm {

  class arm_instruction_factory {
  public:
    static arm_instruction* create_instruction (asml_instruction*);
  protected:
    static arm_funcall* create_funcall (asml_funcall*);
    static arm_affectation* create_affectation (asml_affectation*);
    static arm_addition* create_addition (asml_addition*);
    static arm_soustraction* create_soustraction (asml_soustraction*);
    static arm_condition* create_condition (asml_condition*);
    static arm_negation* create_negation (asml_negation*);
    static arm_mem_create* create_mem_create (asml_mem_create*);
    static arm_mem_read* create_mem_read (asml_mem_read*);
    static arm_mem_write* create_mem_write (asml_mem_write*);
    static arm_closure* create_closure (asml_closure*);
  };

}

#endif //__ARM_INSTRUCTION_FACTORY_H__
