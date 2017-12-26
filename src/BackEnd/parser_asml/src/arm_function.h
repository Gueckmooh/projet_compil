#include <string>
#include <map>
#include <list>
#include <cassert>

#ifndef __ARM_FUNCTION_H__
#define __ARM_FUNCTION_H__

#include "arm_function_generator.h"

using namespace std;

namespace arm {

  class arm_function {
    friend class arm_function_generator;
  public:
    static void initialize (void);
    static void set_processed_function (string);
    static string process_refs (void);
    static string add_ref (string);
  protected:
    static list<string>* funcnames_list;
    static string processed_function;
    static map<string, string>* ref_map;
  };

}

#endif // __ARM_FUNCTION_H__
