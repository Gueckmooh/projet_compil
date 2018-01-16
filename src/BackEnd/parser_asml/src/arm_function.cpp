#include "arm_function.h"

namespace arm {

  list<string>* arm_function::funcnames_list = NULL;
  map<string, string>* arm_function::ref_map = NULL;
  string arm_function::processed_function = "";

  void arm_function::initialize (void) {
    if (funcnames_list == NULL && ref_map == NULL) {
      funcnames_list = new list<string> ();
      ref_map = new map<string, string> ();
    }
  }

  void arm_function::set_processed_function (string name) {
    processed_function = name;
    funcnames_list->push_back(name);
    funcnames_list->unique();
  }

  string arm_function::process_refs (void) {
    string ret;
    if (!ref_map->empty())
      ret += "\t.align 2\n";
    for (map<string, string>::iterator it = ref_map->begin();
         it != ref_map->end();
         it++) {
      assert(it->second.compare("_") != 0);
      ret += it->first + ":\n";
      ret += "\t.word " + it->second.substr(1) + "\n";
    }
    ref_map->clear();
    return ret;
  }

  string arm_function::add_ref (string name) {
    string ret;
    ret += ".L" + to_string(arm_function_generator::lien++);
    ref_map->insert(pair<string, string> (ret, name));
    return ret;
  }

}
