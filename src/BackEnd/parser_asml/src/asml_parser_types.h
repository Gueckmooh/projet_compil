/**
 * \file      asml_parser_types.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Different type needed for ASML parsing
 */

#ifndef __ASML_PARSER_TYPE_H__
#define __ASML_PARSER_TYPE_H__
/*!
  \def ASML_EXP_INT
  \brief OP 1 : Char* - Int value in str
*/
#define ASML_EXP_INT     1  // op1 : un char* - la valeur de l'int en str
/*!
  \def ASML_EXP_IDENT
  \brief OP1 : char * - variable name
*/
#define ASML_EXP_IDENT   2  // op1 : un char* - le nom de la variable
/*!
  \def ASML_EXP_LABEL
  \brief OP1 : char * - label name (starts with _ )
*/
#define ASML_EXP_LABEL   3  // op1 : un char* - la nom du label (commence par _ )
/*!
  \def ASML_EXP_ADD
  \brief OP1 and OP2 : char* - operands value
*/
#define ASML_EXP_ADD     4  // op1 & op2 : des char* - les valeurs des opérandes
/*!
  \def ASML_EXP_SUB
  \brief OP1 and OP2 : char* - operands value
*/
#define ASML_EXP_SUB     5  // op1 & op2 : des char* - les valeurs des opérandes
/*!
  \def ASML_EXP_NEG
  \brief OP1 : char* - operand value
*/
#define ASML_EXP_NEG     6  // op1 : un char* - la valeur de l'opérande
/*!
  \def ASML_EXP_IF
  \brief OP1 : asml_exp_t* condition - OP2 and OP3 : asml_asmt_t tree if OP1 true and false.
*/
#define ASML_EXP_IF      7  // op1 : un asml_exp_t* parmi les conds
                            // op2 : un asml_asmt_t* : l'arbre si op1 vrai
                            // op3 : un asml_asmt_t* : l'arbre si op1 faux
/*!
  \def ASML_COND_EQUAL
  \brief OP1 and OP2 : char* - operands value
*/
#define ASML_COND_EQUAL  8  // op1 & op2 : des char * - les valeurs des opérandes
/*!
  \def ASML_COND_LE
  \brief OP1 and OP2 : char* - operands value
*/
#define ASML_COND_LE     9  // op1 & op2 : des char * - les valeurs des opérandes
/*!
  \def ASML_COND_GE
  \brief OP1 and OP2 : char* - operands value
*/

#define ASML_COND_GE     10 // op1 & op2 : des char * - les valeurs des opérandes
/*!
  \def ASML_EXP_CALL
  \brief OP1 : char* - called function name - OP2 : asml_formal_arg_t* arguments given to function
*/
#define ASML_EXP_CALL    11 // op1 : un char* - le nom de la fonction appelée
                            // op2 : un asml_formal_arg_t* - les arguments à
                            //       passer à la fonction
/*!
  \def ASML_MEM_NEW
  \brief OP1 : char* memory size to allocate, OP2 and OP3 : null
*/
#define ASML_MEM_NEW     12 // op1 : un char* - la taille de la mémoire à allouer
                            // op2 & op3 : NULL
/*!
  \def ASML_MEM_READ
  \brief OP1 : char* target memory pointer - OP2 : char* offset from pointer - OP3 : NULL
*/
#define ASML_MEM_READ    13 // op1 : un char* - le pointeur de la mémoire visée
                            // op2 : un char* - l'offset par rapport au pointeur
                            // op3 : NULL
/*!
  \def ASML_MEM_WRITE
  \brief OP1 : char* target memory pointer - OP2 : char* offset from pointer - OP3 : value to write
*/
#define ASML_MEM_WRITE   14 // op1 : un char* - le pointeur de la mémoire visée
                            // op2 : un char* - l'offset par rapport au pointeur
                            // op3 : un char* - la valeur à écrire
/*!
  \def ASML_EXP_CLOSURE
  \brief Closure
*/
#define ASML_EXP_CLOSURE 15

typedef struct asml_exp {
  int type;   /*! expression type */
  void* op1;  /*! The first operand of the instruction */
  void* op2;  /*! The second operand of the instruction */
  void* op3;  /*! The third operand of the instruction */
} asml_exp_t;  

typedef struct asml_asmt {
  char* op;                /*! Name of variable to allocate. If final expression : NULL */
  asml_exp_t* exp;         /*! Instruction  */
  struct asml_asmt* next;  /*! Next instruction, if final expression : NULL*/
                    
} asml_asmt_t;

typedef struct asml_formal_arg {
  char* val;                     /*! Argument name  */
  struct asml_formal_arg* next;  /*! Pointer to next argument, if last : NULL */
                                 
} asml_formal_arg_t;

typedef struct {
  char* name;               /*! Function name                     */
  asml_formal_arg_t* args;  /*! Pointeur to chained list of arguments */
  asml_asmt_t* asmt;        /*! Pointeur to instruction tree */
} asml_function_t;                      


#endif // __ASML_PARSER_TYPE_H__
