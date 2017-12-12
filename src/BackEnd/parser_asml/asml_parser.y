%{



%}

%token LPAREN
%token RPAREN
%token PLUS
%token EQUAL
%token FEQUAL
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

%%

ident_or_imm:
| INT
| IDENT

exp:
| NOP
| LPAREN exp RPAREN
| INT
| IDENT
| LABEL
| NEG IDENT
| FNEG IDENT
| FADD IDENT IDENT
| FSUB IDENT IDENT
| FMUL IDENT IDENT
| FDIV IDENT IDENT
| NEW ident_or_imm
| ADD IDENT ident_or_imm
| SUB IDENT ident_or_imm
| MEM LPAREN IDENT PLUS ident_or_imm RPAREN
| MEM LPAREN IDENT PLUS ident_or_imm RPAREN ASSIGN IDENT
| IF IDENT EQUAL ident_or_imm THEN asmt ELSE asmt
| IF IDENT LE ident_or_imm THEN asmt ELSE asmt
| IF IDENT GE ident_or_imm THEN asmt ELSE asmt
| IF IDENT FEQUAL IDENT THEN asmt ELSE asmt
| IF IDENT FLE IDENT THEN asmt ELSE asmt
| CALL LABEL formal_args
| CALLCLO IDENT formal_args

asmt:
| LPAREN asmt RPAREN
| LET IDENT EQUAL exp IN asmt
| exp

formal_args:
| IDENT formal_args
| IDENT
| NIL

fundefs:
| LET UNDERSC EQUAL asmt
| LET LABEL EQUAL FLOAT fundefs
| LET LABEL formal_args EQUAL asmt fundefs

toplevel:
|  fundefs
