#include "asml.h"
#include "arm_instruction.h"
#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_AFFECTATION_H__
#define __ARM_AFFECTATION_H__

namespace arm {

  class arm_affectation : public arm_instruction {
  public:
    virtual string get_instruction (void);
  protected:
  };

}

#endif //__ARM_AFFECTATION_H__
