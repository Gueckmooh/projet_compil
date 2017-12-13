%{
#include <iostream>
#include <string>
#include "asml_parser.h"
using namespace std;
extern string name;
static yyFlexLexer lexer;
%}

%option noyywrap

%option c++

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
{NIL}     { cout << "NIL" << endl; return NIL; }
{DIGIT}+  { cout << "INT" << endl; return INT; }
{LPAREN}  { cout << "LPAREN" << endl; return LPAREN; }
{RPAREN}  { cout << "RPAREN" << endl; return RPAREN; }
{PLUS}    { cout << "PLUS" << endl; return PLUS; }
{EQUAL}   { cout << "EQUAL" << endl; return EQUAL; }
{FEQUAL}  { cout << "FEQUAL" << endl; return FEQUAL; }
{LE}      { cout << "LE" << endl; return LE; }
{FLE}     { cout << "FLE" << endl; return FLE; }
{GE}      { cout << "GE" << endl; return GE; }
{IF}      { cout << "IF" << endl; return IF; }
{THEN}    { cout << "THEN" << endl; return THEN; }
{ELSE}    { cout << "ELSE" << endl; return ELSE; }
{LET}     { cout << "LET" << endl; return LET; }
{IN}      { cout << "IN" << endl; return IN; }
{DOT}     { cout << "DOT" << endl; return DOT; }
{NEG}     { cout << "NEG" << endl; return NEG; }
{FNEG}    { cout << "FNEG" << endl; return FNEG; }
{MEM}     { cout << "MEM" << endl; return MEM; }
{FMUL}    { cout << "FMUL" << endl; return FMUL; }
{FDIV}    { cout << "FDIV" << endl; return FDIV; }
{FSUB}    { cout << "FSUB" << endl; return FSUB; }
{FADD}    { cout << "FADD" << endl; return FADD; }
{ASSIGN}  { cout << "ASSIGN" << endl; return ASSIGN; }
{ADD}     { cout << "ADD" << endl; return ADD; }
{SUB}     { cout << "SUB" << endl; return SUB; }
{CALL}    { cout << "CALL" << endl; return CALL; }
{NEW}     { cout << "NEW" << endl; return NEW; }
{NOP}     { cout << "NOP" << endl; return NOP; }
{APPCLO}  { cout << "APPCLO" << endl; return APPCLO; }
{UNDERSC} { cout << "UNDERSC" << endl; return UNDERSC; }
{UNDERSC}({DIGIT}|{LOWER}|{UPPER}|{UNDERSC})*   {
    name = yytext;
    cout << "LABEL" << endl;
    return LABEL; }
{LOWER}({DIGIT}|{LOWER}|{UPPER}|{UNDERSC})*   {
    name = yytext;
    cout << "IDENT" << endl;
    return IDENT; }


%%
int yylex (void) {
    return lexer.yylex();
 }
