#include <string>

#ifndef __ASML_BOOLEAN_H__
#define __ASML_BOOLEAN_H__

using namespace std;

namespace asml {

  class asml_boolean {
  public:
    static const int CONJONCTION = 1; // TODO ??
    static const int DISJONCTION = 2; // TODO ??
    static const int LT = 3;
    static const int GT = 4;
    static const int LE = 5;
    static const int GE = 6;
    static const int EQUAL = 7;

    asml_boolean (int);
    virtual ~asml_boolean (void) {};

    virtual void set_op1 (string);
    virtual void set_op2 (string);

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual int get_type (void);
  protected:
    int type_id;
    string op1;
    string op2;
  };

}

#endif //__ASML_BOOLEAN_H__
