#include <string>

#ifndef __ASML_VARIABLE_H__
#define __ASML_VARIABLE_H__

using namespace std;

namespace asml {

  class asml_variable {
    friend class asml_factory;
  public:
    virtual ~asml_variable (void) {};

    static const int INTEGER = 1;

    virtual void set_name (string);

    virtual int get_type(void);
    virtual string get_name (void) const;
    //string to_string (void);
  protected:
    int type_id;
    string name;
  };

}

#endif //__ASML_VARIABLE_H__
