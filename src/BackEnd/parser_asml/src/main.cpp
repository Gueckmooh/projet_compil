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

//list<asml_function*>* asml_list;
asml_factory factory;

int main (void) {
  asml_function* fun;
  factory.current_instr = 0;
  factory.current_var = 0;
  factory.current_instr = 0;
  //asml_list = new list<asml_function*> ();
  //asml_list->push_back (new asml_function ("test"));
  yyparse ();
  printf ("%s\n", factory.name);
  /*
  for (int i = 0; i < factory.current_var; i++) {
    printf ("Name = %s\n"
	    "Val = %d\n",
	    factory.vars[i],
	    *factory.vals[i]);
  }
  for (int i = 0; i < factory.current_instr; i++) {
    switch (factory.instr[i]) {
    case ACALL:
      printf ("Function : %s\n", factory.op[i][0]);
      for (int j = 1; factory.op[i][j] != NULL; j++) {
	printf ("Arg %d : %s\n", j, factory.op[i][j]);
      }
    }
  }
  */
  fun = create_function (&factory);
  fun->print();
  arm::arm_generator arm(fun);
  arm.generate();
  delete fun;
  return 0;
}
