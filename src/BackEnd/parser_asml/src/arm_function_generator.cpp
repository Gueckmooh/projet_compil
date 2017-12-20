#include "arm_function_generator.h"

namespace arm {

  int arm_function_generator::lien = 0;

  arm_function_generator::arm_function_generator (asml_function* fun) {
    output = new stringstream ();
    asml = fun;
    name = asml->get_name();
  }

  arm_function_generator::~arm_function_generator (void) {
    delete output;
  }

  string arm_function_generator::get_name (void) {
    return name;
  }

  stringstream* arm_function_generator::generate (void) {
    generate_function();
    return output;
  }

  void arm_function_generator::generate_function (void) {
    fp_offset = 4;
    to_save = "fp, lr";
    pre_process_params();
    pre_process_variables();
    generate_prologue();
    process_params();
    process_instructions();
    pre_process_conditions();
    generate_epilogue();
    *output << name.substr(1) <<":\n";
    *output << prologue;
    *output << processed_params;
    for (vector<arm_instruction*>::iterator it = instructions.begin();
	 it != instructions.end();
	 it++) {
      *output << (*it)->get_instruction();
    }
    *output << epilogue;
  }

  void arm_function_generator::pre_process_params (void) {
    int off = -fp_offset -4;
    vector<asml_variable*>* params = asml->get_params ();
    nb_params = params->size();
    for (vector<asml_variable*>::reverse_iterator it = params->rbegin();
	 it != params->rend();
	 it++) {
      var_offsets.insert(pair<string, string> ((*it)->get_name(), to_string(off)));
      off-=4;
    }
  }

  void arm_function_generator::process_params (void) {
    int nb = 0;
    vector<asml_variable*>::iterator it = asml->param_begin();
    asml_integer* integer;
    while (it != asml->param_end() && nb < 4) {
      switch ((*it)->get_type()) {
      case asml_variable::INTEGER:
	integer = dynamic_cast<asml_integer*>(*it);
	processed_params += "\tstr r" + to_string(nb) + ", [fp, #" +
	  var_offsets.find(integer->get_name())->second +
	  "]\n";
	it++;
	nb++;
	break;
      default:
	break;
      }
    }
  }

  void arm_function_generator::pre_process_variables (void) {
    int off = (-fp_offset -4) - 4 * nb_params;
    cout << -fp_offset << endl;
    vector<asml_variable*>* variables = asml->get_variables ();
    nb_variables = variables->size();
    for (vector<asml_variable*>::reverse_iterator it = variables->rbegin();
	 it != variables->rend();
	 it++) {
      var_offsets.insert(pair<string, string> ((*it)->get_name(), to_string(off)));
      off-=4;
    }
  }

  void arm_function_generator::process_instructions (void) {
    vector<asml_instruction*>::iterator it = asml->instruction_begin ();
    cout << name << " : " << to_string(asml->get_instructions()->size()) << endl;
    arm_instruction* instruction;
    while (it != asml->instruction_end ()) {
      instruction = arm_instruction_factory::create_instruction (*it);
      instruction->set_var_offset (&var_offsets);
      instructions.push_back(instruction);
      it++;
    }
  }

  void arm_function_generator::pre_process_conditions (void) {
    string l;
    arm_condition* cond;
    for (vector<arm_instruction*>::iterator it = instructions.begin();
	 it != instructions.end();
	 it++) {
      if ((*it)->get_type() == arm_instruction::CONDITION) {
	cond = dynamic_cast<arm_condition*>(*it);
	l = ".L" + to_string(lien++);
	cond->set_lFalse (l);
	l = ".L" + to_string(lien++);
	cond->set_lFin (l);
      }
    }
  }

  void arm_function_generator::generate_prologue (void) {
    int stack_reserved = (nb_params + nb_variables) * 4;
    prologue += "\tstmfd sp!, {" + to_save + "}\n";
    prologue += "\tadd fp, sp, #" + to_string(fp_offset) + "\n";
    prologue += "\tsub sp, sp, #" + to_string(stack_reserved+4) + "\n";
  }

  void arm_function_generator::generate_epilogue (void) {
    int stack_reserved = (nb_params + nb_variables) * 4;
    epilogue += "\tadd sp, sp, #" + to_string(stack_reserved+4) + "\n";
    epilogue += "\tsub sp, fp, #" + to_string(fp_offset) + "\n";
    epilogue += "\tldmfd sp!, {" + to_save + "}\n";
    epilogue += "\tbx lr\n";
  }

}
