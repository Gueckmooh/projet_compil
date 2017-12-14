#include "arm_affectation.h"

namespace arm {

  string arm_affectation::get_instruction (void) {
    string instruction;
    string var1, var2;
    vector<string>::iterator it = params.begin();
    var1 = *it++;
    var2 = *it;
    switch (arm_util::type_of(var2)) {
    case arm_util::DIRECT:
      instruction = "\tMOV R0, #";
	instruction += var2;
	instruction += "\n";
      break;
    case arm_util::VARIABLE:
      instruction = "\tLDR R0, [FP, #";
      instruction += offset->find(var2)->second;
      instruction += "]";
      instruction += "\n";
      break;
    default:
      break;
      /* do nothing */
    }
    instruction += "\tSTR R0, [FP, #";
    instruction += offset->find(var1)->second;
    instruction += "]";
    instruction += "\n";
    return instruction;
  }

}
