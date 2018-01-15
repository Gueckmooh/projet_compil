#include <list>
#include <stdio.h>
#include <iostream>

#include "asml.h"
#include "arm.h"

using namespace std;
using namespace asml;
using namespace arm;

int main (void) {
  vector<asml_function*>* function;
  asml_factory::initialize();
  #ifndef __TO_ASML
  arm_generator* generator = NULL;
  #else
  asml_generator* generator = NULL;
  #endif
  asml_parse ();
  function = asml_factory::get_function();
  #ifndef __TO_ASML
  generator = new arm_generator (function);
  #else
  generator = new asml_generator (function);
  #endif
  generator->generate ();
  return 0;
}
