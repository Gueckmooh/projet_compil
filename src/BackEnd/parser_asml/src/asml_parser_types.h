#ifndef __ASML_PARSER_TYPE_H__
#define __ASML_PARSER_TYPE_H__

#define ASML_EXP_INT    1  // op1 : un char* - la valeur de l'int en str
#define ASML_EXP_IDENT  2  // op1 : un char* - le nom de la variable
#define ASML_EXP_LABEL  3  // op1 : un char* - la nom du label (commence par _ )
#define ASML_EXP_ADD    4  // op1 & op2 : des char* - les valeurs des opérandes
#define ASML_EXP_SUB    5  // op1 & op2 : des char* - les valeurs des opérandes
#define ASML_EXP_NEG    6  // op1 : un char* - la valeur de l'opérande
#define ASML_EXP_IF     7  // op1 : un asml_exp_t* un parmis les conds
                           // op2 : un asml_asmt_t* : l'arbre si op1 vrai
                           // op3 : un asml_asmt_t* : l'arbre si op1 faux
#define ASML_COND_EQUAL 8  // op1 & op2 : des char * - les valeurs des opérandes
#define ASML_COND_LE    9  // op1 & op2 : des char * - les valeurs des opérandes
#define ASML_COND_GE    10 // op1 & op2 : des char * - les valeurs des opérandes
#define ASML_EXP_CALL   11 // op1 : un char* - le nom de la fonction appelée
                           // op2 : un asml_formal_arg_t* - les arguments à
                           //       passer à la fonction
#define ASML_MEM_NEW    12
#define ASML_MEM_READ   13
#define ASML_MEM_WRITE  14

typedef struct asml_exp {
  int type;   // Le type de l'expréssion
  void* op1;
  void* op2;
  void* op3;
} asml_exp_t;

typedef struct asml_asmt {
  char* op;                // Le nom de la variable à allouer, si "expression
                           // terminale" doit valloir NULL
  asml_exp_t* exp;         // L'exp de l'instruction
  struct asml_asmt* next;  // L'instruction suivante, si "expression terminale"
                           // doit valloir NULL
} asml_asmt_t;

typedef struct asml_formal_arg {
  char* val;                     // Nom de l'argument
  struct asml_formal_arg* next;  // Pointeur vers l'argument suivant, si dernier
                                 // argument doit valloir NULL
} asml_formal_arg_t;

typedef struct {
  char* name;               // Nom de la fonction
  asml_formal_arg_t* args;  // Pointeur vers liste chainée des arguments
  asml_asmt_t* asmt;        // Pointeur vers l'arbre des instructions
} asml_function_t;

#endif // __ASML_PARSER_TYPE_H__
