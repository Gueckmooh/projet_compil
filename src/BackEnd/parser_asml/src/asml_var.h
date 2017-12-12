#include <string>

#ifndef __ASML_VAR_H__
#define __ASML_VAR_H__

using namespace std;

template <class T>
class asml_var {
public:
  asml_var (T, string);
  void set_name (string);
  void set_val (T);
  string get_name (void) const;
  T get_val (void) const;
  string to_string (void);
protected:
  T val;
  string name;
};

#endif //__ASML_VAR_H__
