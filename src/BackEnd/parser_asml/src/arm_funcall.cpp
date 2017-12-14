#include "arm_funcall.h"

namespace arm {

  string arm_funcall::get_instruction (void) {
    string instruction;
    string var1, varn;
    vector<string>::iterator it = params.begin();
    var1 = *it;
    if (params.size() > 5) {
      
    }
    it = params.begin();
    for (int n = 0; it != params.end(); n++)  {
      switch (arm_util::type_of(var1)) {
      case arm_util::DIRECT:
	if (n <= 3) {
	instruction = "\tMOV R0, #";
	instruction += var1;
	instruction += "\n";
	} else {
	  break;
	}
	break;
      case arm_util::VARIABLE:
	instruction = "\tLDR R0, [FP, #";
	instruction += offset->find(var1)->second;
	instruction += "]";
	instruction += "\n";
	break;
      default:
	break;
	/* do nothing */
      }
    }
    instruction += "\tSTR R0, [FP, #";
    instruction += offset->find(var1)->second;
    instruction += "]";
    instruction += "\n";
    return instruction;
  }

}
