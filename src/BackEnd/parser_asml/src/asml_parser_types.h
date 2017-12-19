#ifndef __ASML_PARSER_TYPE_H__
#define __ASML_PARSER_TYPE_H__

#define ASML_EXP_INT    1
#define ASML_EXP_IDENT  2
#define ASML_EXP_LABEL  3
#define ASML_EXP_ADD    4
#define ASML_EXP_SUB    5
#define ASML_EXP_IF     6
#define ASML_EXP_THEN   7
#define ASML_EXP_ELSE   8
#define ASML_COND_EQUAL 9
#define ASML_COND_LE    10
#define ASML_COND_GE    11
#define ASML_EXP_CALL   12
#define ASML_EXP_NEG    13

typedef struct asml_exp {
  int type;
  void* op1;
  void* op2;
  void* op3;
} asml_exp_t;

typedef struct asml_asmt {
  char* op;
  asml_exp_t* exp;
  struct asml_asmt* next;
} asml_asmt_t;

typedef struct asml_formal_arg {
  char* val;
  struct asml_formal_arg* next;
} asml_formal_arg_t;

#endif // __ASML_PARSER_TYPE_H__
