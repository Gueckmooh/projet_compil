%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asml_factory_stub.h"
int yyparse();
int yylex();
int yyerror(const char* s);
char* params;
char* current;
%}

%union {
    char* token_str;
    int token_int;
    float token_float;
}


%token			LOWER
%token			UPPER
%token	<token_int>	INT
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
%type	<token_int>	exp

%%

fundef:		LET UNDERSC EQUAL asmt { asml_set_function_name ("main"); }
	;

asmt:		LET IDENT EQUAL exp IN asmt   { asml_add_int_variable ($2, $4); }
	|	LET IDENT EQUAL call IN asmt  { asml_add_funcall ($4, $2, params); }
	|	call { asml_add_funcall ($1, "0", params); }
	|	exp {}
	;

exp:	 	INT                    { $$ = $1; }
	;

call:		CALL LABEL param { $$ = $2;}
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
