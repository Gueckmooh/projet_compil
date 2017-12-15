#include <list>
#include <stdio.h>
#include <iostream>
extern "C" {
#include "asml_parser.h"
}
#include "asml_function.h"
#include "asml_factory.h"
#include "arm_generator.h"

using namespace std;
using namespace asml;
using namespace arm;

int main (void) {
  asml_function* function;
  asml_factory::create_function();
  arm_generator* generator;
  yyparse ();
  function = asml_factory::get_function();
  generator = new arm_generator (function);
  generator->generate ();
  return 0;
}
