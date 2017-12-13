#include <list>
extern "C" {
#include "asml_parser.h"
}
#include "asml_function.h"

using namespace std;

list<asml_function*>* asml_list;

int main (void) {
  asml_list = new list<asml_function*> ();
  asml_list->push_back (new asml_function ("test"));
  yyparse ();
  return 0;
}
