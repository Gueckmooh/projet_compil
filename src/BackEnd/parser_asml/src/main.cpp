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
  generator = new arm_generator (function);
  generator->generate ();
  return 0;
}
