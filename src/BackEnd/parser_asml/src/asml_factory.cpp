#include "asml_factory.h"

bool digit (string s) {
  char c = s.front();
  return c <= '9' && c >= '0';
}

bool car (string s) {
  char c = s.front();
  return (c <= 'a' && c >= 'z') || (c <= 'A' && c >= 'Z');
}

asml_function* create_function (asml_factory* af) {
  string name(af->name);
  //string* str;
  asml_instr* instr;
  asml_op* op;
  //int type = 0;
  asml_function* func = new asml_function (name);
  for (int i = 0; i < af->current_var; i++) {
    func->add_var(new asml_var(*af->vals[i], af->vars[i]));
  }
  for (int i = 0; i < af->current_param; i++) {
    func->add_param(new asml_var(0, af->params[i]));
  }
  for (int i = 0; i < af->current_instr; i++) {
    instr = new asml_instr (af->instr[i]);
    for (int j = 0; af->op[i][j]!=NULL; j++) {
      if (*af->op[i][j] == '_')
	op = new asml_op (asml_op::FUNC);
      else if (*af->op[i][j] >= '0' && *af->op[i][j] <= '9')
	op = new asml_op (asml_op::DIRECT);
      else
	op = new asml_op (asml_op::VAR);
      op->set_name(af->op[i][j]);
      instr->add_arg(op);
    }
    func->add_instr(instr);
  }
  /*
  for (int i = 0; i < factory.current_var; i++) {
    printf ("Name = %s\n"
	    "Val = %d\n",
	    factory.vars[i],
	    *factory.vals[i]);
  }
  for (int i = 0; i < factory.current_instr; i++) {
    switch (factory.instr[i]) {
    case ACALL:
      printf ("Function : %s\n", factory.op[i][0]);
      for (int j = 1; factory.op[i][j] != NULL; j++) {
	printf ("Arg %d : %s\n", j, factory.op[i][j]);
      }
    }
  }*/
  return func;
}
