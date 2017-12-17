%{
#include "asml_factory_stub.h"
#include "asml_parser.h"
#include "asml_util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int yyparse();
int yylex();
int yyerror(const char* s);
int hulu = 0;
%}

%code requires {
    typedef struct {
	int type;
	char* op1;
	char* op2;
    } asml_parser_operation;

    typedef struct {
        char* name;
	char* params;
    } asml_parser_funcall;
}

%union {
    char* token_str;
    int token_int;
    float token_float;
    asml_parser_operation token_op;
    asml_parser_funcall token_funcall;
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
%type	<token_funcall>	call
%type	<token_op>	exp
%type	<token_str>	param

%%

prog:		fundef fundef
	|	fundef
	;

fundef:		LET UNDERSC EQUAL asmt      {
		    asml_set_function_name ("main");
		    asml_validate_function();
		    printf ("main, %d\n", hulu++);
                }
	|	LET LABEL EQUAL asmt  {
	            asml_set_function_name ($2+1);
		    asml_validate_function();
		    printf ("%s, %d\n", $2, hulu++);
                }
	|	LET LABEL param EQUAL asmt  {
	            asml_add_int_param ($3);
		    asml_set_function_name ($2+1);
		    asml_validate_function ();
		    printf ("%s, %d\n", $2, hulu++);
                }
	;

asmt:		LET IDENT EQUAL INT IN asmt   {
		    asml_add_int_variable ($2);
		    asml_add_affectation ($2, $4);
		    printf ("%s, %d\n", "asmt", hulu++);
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
	|	LET IDENT EQUAL call IN asmt  {
	            asml_add_int_variable ($2);
		    asml_add_funcall ($4.name, $2, $4.params);
                }
	|	call                          {
	            asml_add_funcall ($1.name, "0", $1.params);
		}
	|	exp                           {
	            switch ($1.type) {
		    case 1:
			asml_add_addition ("0", $1.op1, $1.op2);
			break;
		    case 2:
			asml_add_soustraction ("0", $1.op1, $1.op2);
			break;
		    default:
			break;
		    }
		}
	|	INT                           {
	            asml_add_affectation ("0", $1);
		}
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
	|	ADD IDENT INT              {
		    $$.type = 1;
		    $$.op1 = $2;
		    $$.op2 = $3;
		}
	|	SUB IDENT INT              {
		    $$.type = 2;
		    $$.op1 = $2;
		    $$.op2 = $3;
		}
	;

call:		CALL LABEL param {
		    $$.name = $2; $$.params = $3;
                }
	|	CALL LABEL       {
	            $$.name = $2; $$.params = NULL;
		}
	;

param:		param IDENT {
	            strcpy(strend($1), $2);
		    strcpy(strend($1), " ");
		    $$ = $1;
                }
	|	IDENT       {
	            char* ret = (char*) malloc(sizeof (char)*256);
		    strcpy(ret, $1);
		    strcpy(strend(ret), " ");
		    $$ = ret;
		}
	|	param INT {
	            strcpy(strend($1), $2);
		    strcpy(strend($1), " ");
		    $$ = $1;
                }
	|	INT       {
	            char* ret = (char*) malloc(sizeof (char)*256);
		    strcpy(ret, $1);
		    strcpy(strend(ret), " ");
		    $$ = ret;
		}
	;

%%

int yyerror (const char* s) {
    return 0;
    }
