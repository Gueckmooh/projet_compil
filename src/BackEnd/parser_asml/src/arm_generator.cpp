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
    pre_proceed_instructions();
    pre_proceed_params();
    pre_proceed_variables();
    output->close();
  }

  void arm_generator::pre_process_params (void) {
    int off = -fp_offset;
    vector<asml_variable*>* params = asml->get_params ();
    nb_params = params->length();
    for (vector<asml_variable*>::iterator it = params->rbegin();
	 it != params->rend();
	 it++) {
      var_offsets.insert(pair<string, string> (it->get_name(), string(off)));
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
	processed_params += "\tstr r" + string(nb) + ", [fp, #" +
	  var_offsets.find(integer->get_name()->second) +
	  "]\n";
	break;
      default:
	break;
      }
    }
  }

  void pre_process_variables (void) {
    int off = (-fp_offset) - 4 * nb_params;
    vector<asml_variable*> variables = asml->get_variables ();
    nb_variables = variables->length();
    for (vector<asml_variable*>::iterator it = variables->rbegin();
	 it != variables->rend();
	 it++) {
      var_offsets.insert(pair<string, string> (it->get_name(), string(off)));
      off-=4;
    }
  }

  void arm_generator::process_variables (void) {
    vector<asml_variable*>::iterator it = asml->variable_begin();
    asml_integer* integer;
    while (it != asml->variable_end()) {
      switch ((*it)->get_type()) {
      case asml_variable::INTEGER:
	integer = dynamic_cast<asml_integer*>(*it);
	if (integer.has_value()) {
	  processed_variables += "\tmov r0, #" + string(integer->get_value()) + "\n";
	  processed_variables += "\tstr r0, [fp, #" +
	    var_offsets.find(integer->get_name()->second) +
	    "]\n";
	}
	break;
      default:
	break;
      }
    }
  }

  void arm_generator::pre_process_instructions (void) {
    vector<asml_instruction*>::iterator it = asml->instruction_begin();
    while (it != asml->instruction_end() || !do_save_sp)
      do_save_sp = do_save_sp || (it++)->get_type () == asml_instruction::FUNCALL;
  }

  void arm_generator::process_instructions (void) {
    vector<asml_instruction*>::iterator it = asml->instruction_begin ();
    asml_funcall* funcall;
    while (it != asml->instruction_end ()) {
      switch ((*it)->get_type ()) {
      case asml_instruction::FUNCALL:
	
	break;
      default:
	break;
      }
    }
  }

  void arm_generator::generate_prologue (void) {
    int stack_reserved = (nb_params + nb_variables) * 4;
    string to_save = "fp";
    fp_offset = 0;
    if (do_save_sp) {
      fp_offset += 4;
      to_save += " lr";
    }
    prologue += "\tstmfd sp!, {" + to_save + "}\n";
    prologue += "\tadd fp, sp #";
    prologue += fp_offset;
    prologue += "\n\tsub sp, sp, #";
    prologue += stack_reserved;
    prologue += "\n";
  }

  void generate_epilogue (void);

}
