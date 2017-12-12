#include "asml_instr.h"

asml_instr::asml_instr (int type_id) {
  this->type_id = type_id;
  args = new list<asml_op*> ();
}

asml_instr::~asml_instr (void) {
  asml_op* op;
  while (!args->empty()) {
    op = args->back();
    delete op;
    args->pop_back();
  }
  delete args;
}

void asml_instr::add_arg (asml_op* op) {
  args->push_back(op);
}

list<asml_op*>* asml_instr::get_arg_list (void) const {
  return args;
}

void asml_instr::print (void) {
  list<asml_op*>::iterator it = args->begin();
  switch (type_id) {
  case AFFECT:
    cout << (*it)->to_string() << " <- " << (*(++it))->to_string() << endl;
    break;
  case CALL:
    cout << (*it)->to_string() << " ( ";
    while (it != args->end())
      cout << (*(it++))->to_string() << " ";
    cout << ")" << endl;
  }
}
