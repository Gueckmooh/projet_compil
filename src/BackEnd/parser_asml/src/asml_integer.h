#include <string>
#include "asml_variable.h"

#ifndef __ASML_INTEGER_H__
#define __ASML_INTEGER_H__

using namespace std;

namespace asml {

  class asml_integer : public asml_variable {
  public:
    asml_integer (void);

    virtual void set_value (int);
    virtual void unset_value (void);

    virtual bool has_value (void);
    virtual int get_value (void);
  protected:
    int value;
    bool has_value;
  };

}

#endif //__ASML_INTEGER_H__
