%{

#include <iostream>
#define YY_DECL extern "C" int yylex()

%}

SPACE   [ \t\n\r]
DIGIT   [0-9]
LOWER   [a-z]
UPPER   [A-Z]
LPAREN  '('
RPAREN  ')'
PLUS    '+'
EQUAL   '='
FEQUAL  "=."
LE      "<="
FLE     "<=."
GE      ">="
IF      "if"
THEN    "then"
ELSE    "else"
LET     "let"
IN      "in"
DOT     "."
NEG     "neg"
FNEG    "fneg"
MEM     "mem"
FMUL    "fmul"
FDIV    "fdiv"
FSUB    "fsub"
FADD    "fadd"
ASSIGN  "<-"
ADD     "add"
SUB     "sub"
CALL    "call"
NEW     "new"
NOP     "nop"
APPCLO  "apply_closure"
UNDERSC '_'

%%

{SPACE}+   { }
LPAREN     {return LPAREN;}
RPAREN     {return RPAREN;}
PLUS       {return PLUS;}
EQUAL      {return EQUAL;}
FEQUAL     {return FEQUAL;}
LE         {return LE;}
FLE        {return FLE;}
GE         {return GE;}
IF         {return IF;}
THEN       {return THEN;}
ELSE       {return ELSE;}
LET        {return LET;}
IN         {return IN;}
DOT        {return DOT;}
NEG        {return NEG;}
FNEG       {return FNEG;}
MEM        {return MEM;}
FMUL       {return FMUL;}
FDIV       {return FDIV;}
FSUB       {return FSUB;}
FADD       {return FADD;}
ASSIGN     {return ASSIGN;}
ADD        {return ADD;}
SUB        {return SUB;}
CALL       {return CALL;}
NEW        {return NEW;}
NOP        {return NOP;}
APPCLO     {return APPCLO;}
UNDERSC    {return UNDERSC;}

%%

int yyerror(ptree *p, const char *msg) {
    fprintf(stderr,"Error: %s\n",msg);
    exit(-1);
}
