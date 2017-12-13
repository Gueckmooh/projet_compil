%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asml_factory.h"
int yyparse();
int yylex();
int yyerror(const char* s);
extern asml_factory factory;
%}

%union {
    char* token_str;
    int token_int;
    float token_float;
}


%token LOWER
%token UPPER
%token <token_int> INT
%token LPAREN
%token RPAREN
%token PLUS
%token EQUAL
%token FEQUAL
%token NIL
%token LE
%token FLE
%token GE
%token IF
%token THEN
%token ELSE
%token LET
%token IN
%token DOT
%token NEG
%token FNEG
%token MEM
%token FMUL
%token FDIV
%token FSUB
%token FADD
%token ASSIGN
%token ADD
%token SUB
%token CALL
%token NEW
%token NOP
%token APPCLO
%token CARRAY
%token UNDERSC
%token <token_str> LABEL
%token <token_str> IDENT
%token FLOAT


%%

fundef:		LET UNDERSC EQUAL asmt {
		    char* name = malloc (sizeof("main"));
		    strcpy(name, "main");
		    factory.name = name;
		    }
	;

asmt:		LET IDENT EQUAL exp IN asmt  {
		    char* var = (char*) malloc (sizeof ($2));
		    strcpy(var, $2);
		    factory.vars[factory.current_var] = var;
		    factory.current_var++;
		    }
	|	LET IDENT EQUAL exp          {
		    char* var = (char*) malloc (sizeof ($2));
		    factory.vars[factory.current_var] = var;
		    factory.current_var++;
		    }
	|	LET IDENT EQUAL call IN asmt  { }
	|	call { }
	|	exp { }
	;

exp:	 	INT                    {
		    int* val = (int*) malloc (sizeof(int));
		    *val = $1;
		    factory.vals[factory.current_var] = val;
		    }
	;

call:		CALL LABEL param {
		    char* op = (char*) malloc (sizeof ($2));
		    strcpy(op, $2);
		    factory.op[factory.current_instr][0] = op;
		    factory.instr[factory.current_instr] = ACALL;
		    factory.current_instr++;
		    }
	;

param:		param IDENT {
		    char* op = (char*) malloc (sizeof ($2));
		    strcpy(op, $2);
		    factory.op[factory.current_instr][factory.current_op] = op;
		    factory.current_op++;
		    }
	|	IDENT       {
	            factory.current_op=1;
		    char* op = (char*) malloc (sizeof ($1));
		    strcpy(op, $1);
		    factory.op[factory.current_instr][factory.current_op] = op;
		    factory.current_op++;
		    }
	;

%%

int yyerror (const char* s) {
    return 0;
    }
