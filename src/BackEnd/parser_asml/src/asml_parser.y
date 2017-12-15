%{
#include "asml_factory_stub.h"
#include "asml_parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int yyparse();
int yylex();
int yyerror(const char* s);
char* params;
char* current;
%}

%code requires {
    typedef struct {
	int type;
	char* op1;
	char* op2;
    } asml_operation;
}

%union {
    char* token_str;
    int token_int;
    float token_float;
    asml_operation token_op;
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
%type	<token_str>	call
%type	<token_op>	exp

%%

fundef:		LET UNDERSC EQUAL asmt { asml_set_function_name ("main"); }
	;

asmt:		LET IDENT EQUAL INT IN asmt   {
		    asml_add_int_variable ($2);
		    asml_add_affectation ($2, $4);
		    }
	|	LET IDENT EQUAL exp IN asmt   {
	    asml_add_int_variable ($2);
	    switch ($4.type) {
	    case 1:
	      asml_add_addition ($2, $4.op1, $4.op2);
	      break;
	    case 2:
	      asml_add_soustraction ($2, $4.op1, $4.op2);
	      break;
	    default:
	      break;
	    }
		}
	|	LET IDENT EQUAL call IN asmt  { asml_add_funcall ($4, $2, params); }
	|	call                          { asml_add_funcall ($1, "0", params); }
	|	exp                           {}
	;

exp:	 	ADD IDENT IDENT            {
		    $$.type = 1;
		    $$.op1 = $2;
		    $$.op2 = $3;
		    }
	|	SUB IDENT IDENT            {
		    $$.type = 2;
		    $$.op1 = $2;
		    $$.op2 = $3;
		    }
	;

call:		CALL LABEL param { $$ = $2; }
	;

param:		param IDENT {
            strcpy(current, $2);
	    current+=strlen(current);
	    strcpy(current, " ");
	    current+=strlen(current);
                }
	|	IDENT       {
	    params = (char*) malloc(sizeof (char));
	    current = params;
	    strcpy(current, $1);
	    current+=strlen(current);
	    strcpy(current, " ");
	    current+=strlen(current);
		}
	;

%%

int yyerror (const char* s) {
    return 0;
    }
