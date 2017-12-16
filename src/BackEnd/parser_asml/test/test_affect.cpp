#include <iostream>
#include <vector>
#include <map>
#include "arm_affectation.h"

using namespace std;
using namespace arm;

int main (void) {
  arm_affectation aff;
  map<string, string>* offset = new map<string, string> ();
  aff.params.push_back("a");
  aff.params.push_back("9");
  offset->insert ( pair<string, string> ("a", "-4"));
  aff.offset = offset;
  cout << aff.get_instruction() << endl;
  return 0;
}
