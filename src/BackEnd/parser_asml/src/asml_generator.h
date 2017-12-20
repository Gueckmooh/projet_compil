#include <map>
#include <vector>
#include <string>
#include <fstream>

#ifndef __ASML_GENERATOR_H__
#define __ASML_GENERATOR_H__

#include "asml_function.h"
#include "asml_funcall.h"
#include "asml_affectation.h"
#include "asml_addition.h"
#include "asml_soustraction.h"
#include "asml_condition.h"
#include "asml_negation.h"

using namespace std;

namespace asml {

  class asml_generator {
  public:
    asml_generator(vector<asml_function*>*);
    ~asml_generator(void);
    void set_name (string);
    void generate (void);
  protected:
    void generate_function (void);
    ofstream* output;
    string filename;
    int nb_params;
    int nb_variables;
    int sp_offset;
    int fp_offset;
    bool do_save_sp;
    string prologue;
    string epilogue;
    string processed_params;
    string processed_variables;
    string to_save;

    string name;
    vector<asml_function*>* functions;
    map<string, string> var_offsets;
  };

}


#endif //__ASML_GENERATOR_H__
