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
    static const int MEM_CREATE = 7;
    static const int MEM_WRITE = 8;
    static const int MEM_READ = 9;
    static const int CLOSURE = 10;

    virtual ~arm_instruction (void) {};

    int get_type (void);

    virtual int nb_regs (void) = 0;
    virtual list<string>* get_op_list (void) = 0;
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
