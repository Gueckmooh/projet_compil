#include "asml_generator.h"

namespace asml {

  asml_generator::asml_generator (vector<asml_function*>* functions) {
    this->functions = functions;
    name = "default.asml";
    output = new ofstream ();
  }

  asml_generator::~asml_generator (void) {
    /*
    asml_function* func = NULL;
    while (!functions->empty()) {
      func = functions->back();
      functions->pop_back();
      delete func;
    }
    delete functions;
    */
    output->close();
    delete output;
  }

  void asml_generator::set_name (string name) {
    this->name = name;
  }

  void asml_generator::generate (void) {
    output->open (name);
    asml_function* main = NULL;
    for (vector<asml_function*>::iterator it = functions->begin();
	 it != functions->end();
	 it++) {
      if ((*it)->get_name().compare("main") == 0)
	main = (*it);
      else
	*output << (*it)->generate() << endl;
    }
    if (main != NULL)
      *output << main->generate() << endl;
    output->close();
  }

}
