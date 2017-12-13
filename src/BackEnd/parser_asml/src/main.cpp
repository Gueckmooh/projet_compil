#include <list>
#include "asml_parser.h"
#include "asml_function.h"

list<asml_function>* asml_list;

int main (void) {
  asml_list = new list<asml_function> ();
  asml_list.push_back (new asml_function ("test"));
  yyparse ();
  return 0;
}
