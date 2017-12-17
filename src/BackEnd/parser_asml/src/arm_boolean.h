#include <string>
#include <map>

#ifndef __ARM_BOOLEAN_H__
#define __ARM_BOOLEAN_H__

#include "arm_util.h"

using namespace std;

namespace arm {

  class arm_boolean {
  public:
    static const int CONJONCTION = 1; // TODO ??
    static const int DISJONCTION = 2; // TODO ??
    static const int LT = 3;
    static const int GT = 4;
    static const int LE = 5;
    static const int GE = 6;
    static const int EQUAL = 7;
    static const int NEQUAL = 8;

    arm_boolean (int);
    virtual ~arm_boolean (void) {};

    virtual string get_instruction (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_lFalse (string);

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual int get_type (void);
  protected:
    map<string, string>* offset;
    string lFalse;
    int type_id;
    string cmp;
    string op1;
    string op2;
  };

}

#endif //__ARM_BOOLEAN_H__
