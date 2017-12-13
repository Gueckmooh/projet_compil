%{
#include <stdio.h>
#include <string.h>
int yyparse();
int yylex();
int yyerror(const char* s);
%}

%union {
    char* token_str;
    int token_int;
    float token_float;
}


%token LOWER
%token UPPER
%token INT
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
%token UNDERSC
%token <token_str> LABEL
%token <token_str> IDENT
%token FLOAT


%%

fundef:		LET UNDERSC EQUAL asmt 
	;

asmt:		LET IDENT EQUAL exp IN asmt { printf ("%s\n", $2); }
	|	exp
	;

exp:		CALL LABEL param
	|	INT
	;

param:		IDENT param
	|	IDENT
	;

%%

int yyerror (const char* s) {
    return 0;
    }
