%{
#include <stdio.h>
#include <string.h>
#include "asml_parser.h"
%}

%option noyywrap nounput noinput

LOWER   [a-z]
UPPER   [A-Z]
DIGIT   [0-9]
FLOAT   [+-]?([0-9]*[.])?[0-9]+
SPACE   " "
LPAREN  "("
RPAREN  ")"
PLUS    "+"
EQUAL   "="
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
NIL     "nil"
UNDERSC "_"

%%
{NIL}     { printf("NIL\n"); return NIL; }
{DIGIT}+  { printf("INT\n"); return INT; }
{LPAREN}  { printf("LPAREN\n"); return LPAREN; }
{RPAREN}  { printf("RPAREN\n"); return RPAREN; }
{PLUS}    { printf("PLUS\n"); return PLUS; }
{EQUAL}   { printf("EQUAL\n"); return EQUAL; }
{FEQUAL}  { printf("FEQUAL\n"); return FEQUAL; }
{LE}      { printf("LE\n"); return LE; }
{FLE}     { printf("FLE\n"); return FLE; }
{GE}      { printf("GE\n"); return GE; }
{IF}      { printf("IF\n"); return IF; }
{THEN}    { printf("THEN\n"); return THEN; }
{ELSE}    { printf("ELSE\n"); return ELSE; }
{LET}     { printf("LET\n"); return LET; }
{IN}      { printf("IN\n"); return IN; }
{DOT}     { printf("DOT\n"); return DOT; }
{NEG}     { printf("NEG\n"); return NEG; }
{FNEG}    { printf("FNEG\n"); return FNEG; }
{MEM}     { printf("MEM\n"); return MEM; }
{FMUL}    { printf("FMUL\n"); return FMUL; }
{FDIV}    { printf("FDIV\n"); return FDIV; }
{FSUB}    { printf("FSUB\n"); return FSUB; }
{FADD}    { printf("FADD\n"); return FADD; }
{ASSIGN}  { printf("ASSIGN\n"); return ASSIGN; }
{ADD}     { printf("ADD\n"); return ADD; }
{SUB}     { printf("SUB\n"); return SUB; }
{CALL}    { printf("CALL\n"); return CALL; }
{NEW}     { printf("NEW\n"); return NEW; }
{NOP}     { printf("NOP\n"); return NOP; }
{APPCLO}  { printf("APPCLO\n"); return APPCLO; }
{UNDERSC} { printf("UNDERSC\n"); return UNDERSC; }
{UNDERSC}({DIGIT}|{LOWER}|{UPPER}|{UNDERSC})*   {
    char* new_token = malloc (sizeof (yytext));
    strcpy(new_token, yytext);
    yylval.token_str = yytext;
    printf("LABEL\n");
    return LABEL; }
{LOWER}({DIGIT}|{LOWER}|{UPPER}|{UNDERSC})*   {
    char* new_token = malloc (sizeof (yytext));
    strcpy(new_token, yytext);
    yylval.token_str = yytext;
    printf("IDENT\n");
    return IDENT; }


%%
