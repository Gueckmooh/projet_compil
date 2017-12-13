#include <string>

using namespace std;

#ifndef __ASML_VAR_H__
#define __ASML_VAR_H__

class asml_var {
public:
  asml_var (int, string);
  void set_name (string);
  void set_val (int);
  string get_name (void) const;
  int get_val (void) const;
  string to_string (void);
protected:
  int val;
  string name;
};

#endif //__ASML_VAR_H__
