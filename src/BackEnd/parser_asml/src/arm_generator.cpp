#include "arm_generator.h"

namespace arm {

  arm_generator::arm_generator (asml_function* fun) {
    output = new ofstream ();
    filename = "default.s";
    asml = fun;
    do_save_sp = false;
  }

  arm_generator::~arm_generator (void) {
    output->close();
    delete output;
  }

  void arm_generator::set_name (string name) {
    this->filename = name;
  }

  void arm_generator::generate (void) {
    output->open(filename);
    *output << "\t.text" << endl;
    *output << "\t.global _start" << endl;
    *output << "\t.global main" << endl;
    *output << "_start:" << endl;
    *output << "\tbl main" << endl;
    *output << "\tbl min_caml_exit" << endl;
    generate_function();
    output->close();
  }

  void arm_generator::generate_function (void) {
    fp_offset = 0;
    //if (do_save_sp || true) { // TODO
    to_save = "fp";
    fp_offset += 4;
    to_save += ", lr";
    //}
    //pre_process_instructions();
    pre_process_params();
    pre_process_variables();
    generate_prologue();
    process_params();
    //    process_variables();
    process_instructions();
    generate_epilogue();
    *output << "main:\n";
    *output << prologue;
    *output << processed_params;
    //    *output << processed_variables;
    for (vector<arm_instruction*>::reverse_iterator it = instructions.rbegin();
	 it != instructions.rend();
	 it++) {
      *output << (*it)->get_instruction();
    }
    *output << epilogue;
  }

  void arm_generator::pre_process_params (void) {
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

  void arm_generator::process_params (void) {
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
	nb++;
	break;
      default:
	break;
      }
    }
  }

  void arm_generator::pre_process_variables (void) {
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
  /*
  void arm_generator::process_variables (void) {
    vector<asml_variable*>::iterator it = asml->variable_begin();
    asml_integer* integer;
    while (it != asml->variable_end()) {
      switch ((*it)->get_type()) {
      case asml_variable::INTEGER:
	integer = dynamic_cast<asml_integer*>(*it);
	if (integer->has_value()) {
	  processed_variables += "\tmov r0, #" + to_string(integer->get_value()) + "\n";
	  processed_variables += "\tstr r0, [fp, #" +
	    var_offsets.find(integer->get_name())->second +
	    "]\n";
	}
	it++;
	break;
      default:
	break;
      }
    }
  }
  */
  /*
  void arm_generator::pre_process_instructions (void) {
    vector<asml_instruction*>::iterator it = asml->instruction_begin();
    while (it != asml->instruction_end())
      do_save_sp = do_save_sp || (*it++)->get_type () == asml_instruction::FUNCALL;
  }
  */
  void arm_generator::process_instructions (void) {
    vector<asml_instruction*>::iterator it = asml->instruction_begin ();
    arm_instruction* instruction;
    while (it != asml->instruction_end ()) {
      instruction = arm_instruction_factory::create_instruction (*it);
      instruction->set_var_offset (&var_offsets);
      instructions.push_back(instruction);
      it++;
    }
  }

  void arm_generator::generate_prologue (void) {
    int stack_reserved = (nb_params + nb_variables) * 4;
    prologue += "\tstmfd sp!, {" + to_save + "}\n";
    prologue += "\tadd fp, sp, #" + to_string(fp_offset) + "\n";
    prologue += "\tsub sp, sp, #" + to_string(stack_reserved+4) + "\n";
  }

  void arm_generator::generate_epilogue (void) {
    int stack_reserved = (nb_params + nb_variables) * 4;
    epilogue += "\tadd sp, sp, #" + to_string(stack_reserved+4) + "\n";
    epilogue += "\tsub sp, fp, #" + to_string(fp_offset) + "\n";
    epilogue += "\tldmfd sp!, {" + to_save + "}\n";
    epilogue += "\tbx lr\n";
  }

}
