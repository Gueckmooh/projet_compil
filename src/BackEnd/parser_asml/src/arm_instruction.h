#include <string>
#include <map>
#include <vector>
#include <list>

#ifndef __ARM_INSTRUCION_H__
#define __ARM_INSTRUCION_H__

#include "arm_util.h"

namespace arm {

  class arm_instruction {
  public:
    static const int FUNCALL = 1;
    static const int AFFECTATION = 2;
    static const int ADDITION = 3;
    static const int SOUSTRACTION = 4;
    static const int CONDITION = 5;
    static const int NEGATION = 6;

    virtual ~arm_instruction (void) {};

    int get_type (void);

    virtual string get_instruction (void) = 0;
    virtual void set_var_offset (map<string, string>*);
    void add_param (string);
  protected:
    int type_id;
    map<string, string>* offset;
    vector<string> params;
  };

}

#endif //__ARM_INSTRUCION_H__
