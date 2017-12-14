#include "arm_generator.h"

namespace arm {

  arm_generator::arm_generator (asml_function* fun) {
    output = new ofstream ();
    filename = "default.s";
    asml = fun;
  }

  arm_generator::~arm_generator (void) {
    output->close();
    delete output;
  }

  void arm_generator::set_name (string name) {
    this->filename = name;
  }

  void arm_generator::generate (void) {
    output->open(filename);
    *output << "\t.text" << endl;
    *output << "\t.global _start" << endl;
    output->close();
  }

}
