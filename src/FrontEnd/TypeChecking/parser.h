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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    INT = 259,
    FLOAT = 260,
    NOT = 261,
    MINUS = 262,
    PLUS = 263,
    MINUS_DOT = 264,
    PLUS_DOT = 265,
    AST_DOT = 266,
    SLASH_DOT = 267,
    EQUAL = 268,
    LESS_GREATER = 269,
    LESS_EQUAL = 270,
    GREATER_EQUAL = 271,
    LESS = 272,
    GREATER = 273,
    IF = 274,
    THEN = 275,
    ELSE = 276,
    IDENT = 277,
    LET = 278,
    IN = 279,
    REC = 280,
    COMMA = 281,
    ARRAY_CREATE = 282,
    DOT = 283,
    LESS_MINUS = 284,
    SEMICOLON = 285,
    LPAREN = 286,
    RPAREN = 287,
    TEOF = 288,
    prec_let = 289,
    prec_if = 290,
    prec_unary_minus = 291,
    prec_app = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "parser.y" /* yacc.c:1909  */

    int tok_int;
    float tok_float;
    id tok_id;
    int tok_bool;
    ptree tok_tree;
    plist tok_list;
    pfundef tok_fd;

#line 102 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (ptree *ast);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
