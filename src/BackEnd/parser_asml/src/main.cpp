#include <list>
#include <stdio.h>
#include <iostream>
/*
extern "C" {
#include "asml_parser.h"
}
#include "asml_function.h"
#include "asml_instruction.h"
#include "asml_factory.h"
#include "arm_generator.h"
#include "asml_generator.h"
*/

#include "asml.h"
#include "arm.h"

using namespace std;
using namespace asml;
using namespace arm;

int main (void) {
  vector<asml_function*>* function;
  asml_factory::initialize();
  arm_generator* generator = NULL;
  asml_generator* asml_gen = NULL;
  asml_gen = asml_gen;
  generator = generator;
  asml_parse ();
  function = asml_factory::get_function();
  /*
  for (vector<asml_function*>::iterator it = function->begin();
       it != function->end();
       it++) {
    for (vector<asml_instruction*>::iterator it2 = (*it)->instruction_begin();
	 it2 != (*it)->instruction_end();
	 it2++) {
      cout << (*it2)->get_type() << endl;
    }
    cout << endl;
  }
  */
  //generator = new arm_generator (function);
  //generator->generate ();
  asml_gen = new asml_generator (function);
  asml_gen->generate();
  return 0;
}
