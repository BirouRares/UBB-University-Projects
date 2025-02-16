/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LANG_TAB_H_INCLUDED
# define YY_YY_LANG_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    REAL = 259,                    /* REAL  */
    STR = 260,                     /* STR  */
    CHAR = 261,                    /* CHAR  */
    BOOL = 262,                    /* BOOL  */
    READ = 263,                    /* READ  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    WRITE = 266,                   /* WRITE  */
    WHILE = 267,                   /* WHILE  */
    REPORT = 268,                  /* REPORT  */
    ARR = 269,                     /* ARR  */
    AND = 270,                     /* AND  */
    OR = 271,                      /* OR  */
    PLUS = 272,                    /* PLUS  */
    MINUS = 273,                   /* MINUS  */
    TIMES = 274,                   /* TIMES  */
    DIV = 275,                     /* DIV  */
    MOD = 276,                     /* MOD  */
    BIGGEREQ = 277,                /* BIGGEREQ  */
    LESSEQ = 278,                  /* LESSEQ  */
    BIGGER = 279,                  /* BIGGER  */
    LESS = 280,                    /* LESS  */
    EQQ = 281,                     /* EQQ  */
    EQ = 282,                      /* EQ  */
    NEQ = 283,                     /* NEQ  */
    SQBRACKETOPEN = 284,           /* SQBRACKETOPEN  */
    SQBRACKETCLOSE = 285,          /* SQBRACKETCLOSE  */
    OPEN = 286,                    /* OPEN  */
    CLOSE = 287,                   /* CLOSE  */
    BRACKETOPEN = 288,             /* BRACKETOPEN  */
    BRACKETCLOSE = 289,            /* BRACKETCLOSE  */
    DOT = 290,                     /* DOT  */
    COMMA = 291,                   /* COMMA  */
    COLON = 292,                   /* COLON  */
    SEMICOLON = 293,               /* SEMICOLON  */
    END_BLOCK = 294,               /* END_BLOCK  */
    BEGIN_BLOCK = 295,             /* BEGIN_BLOCK  */
    ENDL = 296,                    /* ENDL  */
    IDENTIFIER = 297,              /* IDENTIFIER  */
    INTCONSTANT = 298,             /* INTCONSTANT  */
    STRINGCONSTANT = 299           /* STRINGCONSTANT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LANG_TAB_H_INCLUDED  */
