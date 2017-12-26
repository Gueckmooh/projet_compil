#include "arm_generator.h"

namespace arm {

  arm_generator::arm_generator (vector<asml_function*>* fun) {
    output = new ofstream ();
    filename = "default.s";
    asml = fun;
    do_save_sp = false;
    for (vector<asml_function*>::iterator it = asml->begin();
	 it != asml->end();
	 it++)
      generators.push_back(new arm_function_generator(*it));
  }

  arm_generator::~arm_generator (void) {
    output->close();
    arm_function::initialize();
    delete output;
  }

  void arm_generator::set_name (string name) {
    this->filename = name;
  }

  void arm_generator::generate (void) {
    output->open(filename);
    *output << "\t.text" << endl;
    *output << "\t.global _start" << endl;
    for (vector<arm_function_generator*>::iterator it = generators.begin();
	 it != generators.end();
	 it++)
      *output << "\t.global " << (*it)->get_name() << endl;
    *output << "_start:" << endl;
    *output << "\tbl __mem_init" << endl;
    *output << "\tbl main" << endl;
    *output << "\tbl min_caml_exit" << endl;
    generate_function();
    output->close();
  }

  void arm_generator::generate_function (void) {
    stringstream* ss;
    for (vector<arm_function_generator*>::iterator it = generators.begin();
	 it != generators.end();
	 it++) {
      ss = (*it)->generate();
      *output << ss->str() << endl;
    }
  }

}
