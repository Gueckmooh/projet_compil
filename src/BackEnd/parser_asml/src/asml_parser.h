/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_ASML_SRC_ASML_PARSER_H_INCLUDED
# define YY_ASML_SRC_ASML_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef ASML_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define ASML_DEBUG 1
#  else
#   define ASML_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define ASML_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined ASML_DEBUG */
#if ASML_DEBUG
extern int asml_debug;
#endif
/* "%code requires" blocks.  */
#line 17 "src/asml_parser.y" /* yacc.c:1909  */


    #include "asml_parser_types.h"


#line 58 "src/asml_parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef ASML_TOKENTYPE
# define ASML_TOKENTYPE
  enum asml_tokentype
  {
    LOWER = 258,
    UPPER = 259,
    INT = 260,
    LPAREN = 261,
    RPAREN = 262,
    PLUS = 263,
    EQUAL = 264,
    FEQUAL = 265,
    NIL = 266,
    LE = 267,
    FLE = 268,
    GE = 269,
    IF = 270,
    THEN = 271,
    ELSE = 272,
    LET = 273,
    IN = 274,
    DOT = 275,
    NEG = 276,
    FNEG = 277,
    MEM = 278,
    FMUL = 279,
    FDIV = 280,
    FSUB = 281,
    FADD = 282,
    ASSIGN = 283,
    ADD = 284,
    SUB = 285,
    CALL = 286,
    NEW = 287,
    NOP = 288,
    APPCLO = 289,
    CARRAY = 290,
    UNDERSC = 291,
    LABEL = 292,
    IDENT = 293,
    FLOAT = 294
  };
#endif

/* Value type.  */
#if ! defined ASML_STYPE && ! defined ASML_STYPE_IS_DECLARED

union ASML_STYPE
{
#line 23 "src/asml_parser.y" /* yacc.c:1909  */

    char* token_str;
    asml_asmt_t* token_asmt;
    asml_exp_t* token_exp;
    asml_formal_arg_t* token_args;

#line 117 "src/asml_parser.h" /* yacc.c:1909  */
};

typedef union ASML_STYPE ASML_STYPE;
# define ASML_STYPE_IS_TRIVIAL 1
# define ASML_STYPE_IS_DECLARED 1
#endif


extern ASML_STYPE asml_lval;

int asml_parse (void);

#endif /* !YY_ASML_SRC_ASML_PARSER_H_INCLUDED  */
