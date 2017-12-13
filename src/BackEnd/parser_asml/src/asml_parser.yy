%{
#include <iostream>
#include <string>
#include <list>
#include "asml.h"
using namespace std;
int yyparse();
int yylex();
int yyerror(string s);
string name;
extern list<asml_function>* asml_list;
asml_function* current;
%}

%union {
  int tok_id;
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
%token LABEL
%token IDENT
%token FLOAT


%%

fundef:		LET UNDERSC EQUAL asmt {
		    current = asml_list->front();
		    current->set_name("main"); }
	;

asmt:		LET IDENT EQUAL exp IN asmt { 
	|	exp
	;

exp:		CALL LABEL param
	|	INT
	;

param:		IDENT param
	|	IDENT
	;

%%

int yyerror (string s) {
    cerr << s << endl;
    return 0;
    }
