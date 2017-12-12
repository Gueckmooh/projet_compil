#include <string>

using namespace std;

template <class T>
class asml_var {
public:
  asml_var (T, string);
  virtual void set_name (string);
  virtual void set_init_val (T);
  virtual T get_init_val (void) const;
protected:
  T val;
  string name;
};
