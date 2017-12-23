%{
//#include "asml_factory_stub.h"
#include "asml_parser.h"
//#include "asml_util.h"
#include "asml_parser_types.h"
#include "asml_parser_driver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int asml_parse();
int asml_lex();
int asml_error(const char* s);
%}

%define api.prefix {asml_}

%code requires {

    #include "asml_parser_types.h"

}

%union {
    char* token_str;
    asml_asmt_t* token_asmt;
    asml_exp_t* token_exp;
    asml_formal_arg_t* token_args;
}


%token			LOWER
%token			UPPER
%token	<token_str>	INT
%token			LPAREN
%token			RPAREN
%token			PLUS
%token			EQUAL
%token			FEQUAL
%token			NIL
%token			LE
%token			FLE
%token			GE
%token			IF
%token			THEN
%token			ELSE
%token			LET
%token			IN
%token			DOT
%token			NEG
%token			FNEG
%token			MEM
%token			FMUL
%token			FDIV
%token			FSUB
%token			FADD
%token			ASSIGN
%token			ADD
%token			SUB
%token			CALL
%token			NEW
%token			NOP
%token			APPCLO
%token			CARRAY
%token			UNDERSC
%token	<token_str>	LABEL
%token	<token_str>	IDENT
%token			FLOAT

%type	<token_asmt>	asmt
%type	<token_exp>	exp
%type	<token_args>	formal_args
%type	<token_str>	ident_or_imm
%type	<token_exp>	cond

%%

toplevel:
	|  	fundefs
;

fundefs:
	| 	LET UNDERSC EQUAL asmt                    { asml_parser_create_function(asml_parser_package_function ("main", NULL, $4)); }
	| 	LET LABEL formal_args EQUAL asmt fundefs  { asml_parser_create_function(asml_parser_package_function ($2, $3, $5)); }
;

asmt: 		LPAREN asmt RPAREN           { $$ = $2; }
	| 	LET IDENT EQUAL exp IN asmt  { $$ = asml_parser_add_asmt ($2, $4, $6); }
	| 	exp                          { $$ = asml_parser_add_asmt (NULL, $1, NULL); }
;

exp: 		LPAREN exp RPAREN                                       { $$ = $2; }
	| 	INT                                                     { $$ = asml_parser_create_exp (ASML_EXP_INT, $1, NULL, NULL); }
	| 	IDENT                                                   { $$ = asml_parser_create_exp (ASML_EXP_IDENT, $1, NULL, NULL); }
	| 	LABEL                                                   { $$ = asml_parser_create_exp (ASML_EXP_LABEL, $1, NULL, NULL); }
	| 	ADD IDENT ident_or_imm                                  { $$ = asml_parser_create_exp (ASML_EXP_ADD, $2, $3, NULL); }
	| 	SUB IDENT ident_or_imm                                  { $$ = asml_parser_create_exp (ASML_EXP_SUB, $2, $3, NULL); }
	|	NEG IDENT                                               { $$ = asml_parser_create_exp (ASML_EXP_NEG, $2, NULL, NULL); }
	| 	IF cond THEN asmt ELSE asmt                             { $$ = asml_parser_create_exp (ASML_EXP_IF, $2, $4, $6); }
	| 	CALL LABEL formal_args                                  { $$ = asml_parser_create_exp (ASML_EXP_CALL, $2, $3, NULL); }
	|	CALL LABEL                                              { $$ = asml_parser_create_exp (ASML_EXP_CALL, $2, NULL, NULL); }
	|	NEW ident_or_imm                                        { $$ = asml_parser_create_exp (ASML_MEM_NEW, $2, NULL, NULL); }
	| 	MEM LPAREN IDENT PLUS ident_or_imm RPAREN               { $$ = asml_parser_create_exp (ASML_MEM_READ, $3, $5, NULL); }
	| 	MEM LPAREN IDENT PLUS ident_or_imm RPAREN ASSIGN IDENT  { $$ = asml_parser_create_exp (ASML_MEM_WRITE, $3, $5, $8); }
;

cond:		IDENT EQUAL ident_or_imm  { $$ = asml_parser_create_exp (ASML_COND_EQUAL, $1, $3, NULL); }
	|	IDENT LE ident_or_imm     { $$ = asml_parser_create_exp (ASML_COND_LE, $1, $3, NULL); }
	|	IDENT GE ident_or_imm     { $$ = asml_parser_create_exp (ASML_COND_GE, $1, $3, NULL); }
	;

formal_args: 	IDENT formal_args  { $$ = asml_parser_add_arg ($1, $2); }
	| 	IDENT              { $$ = asml_parser_add_arg ($1, NULL); }
;

ident_or_imm: 	INT
	| 	IDENT
;

%%

int asml_error (const char* s) {
    fprintf(stderr, "%s\n", s);
    return 1;
}
