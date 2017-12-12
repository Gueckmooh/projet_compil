#include <string>

using namespace std;

#ifndef __ASML_OP_H__
#define __ASML_OP_H__

class asml_op {
public:
  static const int FUNC = 1;
  static const int VAR = 2;
  static const int DIRECT = 3;

  asml_op (int);
  void set_name (string);
  void set_val (int);
  string get_name (void);
  int get_val (void);
  int get_type (void);
  string to_string (void);
protected:
  int type_id;
  string name;
  int val;
};

#endif //__ASML_OP_H__
