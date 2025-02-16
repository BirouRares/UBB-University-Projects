/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lang.y"

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

int yyerror(const char *s);

#line 81 "lang.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "lang.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_REAL = 4,                       /* REAL  */
  YYSYMBOL_STR = 5,                        /* STR  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_READ = 8,                       /* READ  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WRITE = 11,                     /* WRITE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_REPORT = 13,                    /* REPORT  */
  YYSYMBOL_ARR = 14,                       /* ARR  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_TIMES = 19,                     /* TIMES  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_MOD = 21,                       /* MOD  */
  YYSYMBOL_BIGGEREQ = 22,                  /* BIGGEREQ  */
  YYSYMBOL_LESSEQ = 23,                    /* LESSEQ  */
  YYSYMBOL_BIGGER = 24,                    /* BIGGER  */
  YYSYMBOL_LESS = 25,                      /* LESS  */
  YYSYMBOL_EQQ = 26,                       /* EQQ  */
  YYSYMBOL_EQ = 27,                        /* EQ  */
  YYSYMBOL_NEQ = 28,                       /* NEQ  */
  YYSYMBOL_SQBRACKETOPEN = 29,             /* SQBRACKETOPEN  */
  YYSYMBOL_SQBRACKETCLOSE = 30,            /* SQBRACKETCLOSE  */
  YYSYMBOL_OPEN = 31,                      /* OPEN  */
  YYSYMBOL_CLOSE = 32,                     /* CLOSE  */
  YYSYMBOL_BRACKETOPEN = 33,               /* BRACKETOPEN  */
  YYSYMBOL_BRACKETCLOSE = 34,              /* BRACKETCLOSE  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_COMMA = 36,                     /* COMMA  */
  YYSYMBOL_COLON = 37,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 38,                 /* SEMICOLON  */
  YYSYMBOL_END_BLOCK = 39,                 /* END_BLOCK  */
  YYSYMBOL_BEGIN_BLOCK = 40,               /* BEGIN_BLOCK  */
  YYSYMBOL_ENDL = 41,                      /* ENDL  */
  YYSYMBOL_IDENTIFIER = 42,                /* IDENTIFIER  */
  YYSYMBOL_INTCONSTANT = 43,               /* INTCONSTANT  */
  YYSYMBOL_STRINGCONSTANT = 44,            /* STRINGCONSTANT  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_stmtlist = 47,                  /* stmtlist  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_simplstmt = 49,                 /* simplstmt  */
  YYSYMBOL_declaration = 50,               /* declaration  */
  YYSYMBOL_type = 51,                      /* type  */
  YYSYMBOL_type1 = 52,                     /* type1  */
  YYSYMBOL_arraydecl = 53,                 /* arraydecl  */
  YYSYMBOL_assignstmt = 54,                /* assignstmt  */
  YYSYMBOL_operator = 55,                  /* operator  */
  YYSYMBOL_expression = 56,                /* expression  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_factor = 58,                    /* factor  */
  YYSYMBOL_iostmt = 59,                    /* iostmt  */
  YYSYMBOL_structstmt = 60,                /* structstmt  */
  YYSYMBOL_ifstmt = 61,                    /* ifstmt  */
  YYSYMBOL_condition = 62,                 /* condition  */
  YYSYMBOL_RELATION = 63,                  /* RELATION  */
  YYSYMBOL_whilestmt = 64                  /* whilestmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   89

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  104

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    64,    65,    68,    69,    72,    73,    74,
      77,    80,    81,    84,    85,    86,    87,    88,    91,    94,
      97,    98,    99,   100,   101,   104,   105,   108,   109,   110,
     113,   114,   115,   116,   119,   120,   121,   122,   123,   126,
     127,   130,   131,   134,   135,   136,   139,   140,   141,   142,
     143,   144,   145,   148
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "REAL", "STR",
  "CHAR", "BOOL", "READ", "IF", "ELSE", "WRITE", "WHILE", "REPORT", "ARR",
  "AND", "OR", "PLUS", "MINUS", "TIMES", "DIV", "MOD", "BIGGEREQ",
  "LESSEQ", "BIGGER", "LESS", "EQQ", "EQ", "NEQ", "SQBRACKETOPEN",
  "SQBRACKETCLOSE", "OPEN", "CLOSE", "BRACKETOPEN", "BRACKETCLOSE", "DOT",
  "COMMA", "COLON", "SEMICOLON", "END_BLOCK", "BEGIN_BLOCK", "ENDL",
  "IDENTIFIER", "INTCONSTANT", "STRINGCONSTANT", "$accept", "program",
  "stmtlist", "stmt", "simplstmt", "declaration", "type", "type1",
  "arraydecl", "assignstmt", "operator", "expression", "term", "factor",
  "iostmt", "structstmt", "ifstmt", "condition", "RELATION", "whilestmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-34)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -1,   -26,    20,    -6,   -34,     4,    -4,    23,    -4,   -16,
      21,    -6,   -34,   -34,   -34,   -34,   -34,   -34,   -34,    14,
      15,    -4,    29,   -34,    18,    30,   -34,    19,   -19,    22,
      -4,    12,   -34,   -34,    28,   -34,    32,   -33,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,    -4,   -34,   -34,   -34,   -34,
     -34,    -4,    24,    33,    34,    35,    38,    36,   -34,   -34,
     -34,   -34,   -34,   -34,    40,   -34,   -34,   -34,   -34,   -34,
      39,    42,    37,   -34,    -6,   -34,   -34,   -34,   -34,    -6,
      26,   -34,   -34,    -4,    -4,    -2,    41,    43,   -34,   -34,
      44,    45,    47,    49,    51,   -34,   -34,    31,    -6,    52,
      50,   -34,    48,   -34
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     3,     5,     7,     8,     9,     6,    39,    40,     0,
       0,     0,    27,    28,     0,    25,    29,     0,     0,     0,
       0,     0,     2,     4,     0,    30,     0,     0,    46,    47,
      48,    49,    50,    51,    52,     0,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,    19,    13,
      14,    15,    16,    17,     0,    10,    11,    12,    34,    33,
       0,     0,    43,    26,     0,    38,    35,    36,    37,     0,
       0,    31,    32,     0,     0,     0,     0,     0,    44,    45,
       0,     0,     0,     0,     0,    41,    53,     0,     0,     0,
       0,    18,     0,    42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -34,   -34,   -11,   -34,   -34,   -34,   -34,     1,   -34,   -34,
     -34,   -17,   -34,   -34,   -34,   -34,   -34,    -7,   -34,   -34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    10,    11,    12,    13,    65,    66,    67,    14,
      51,    24,    25,    26,    15,    16,    17,    27,    45,    18
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      33,    29,     5,     6,    36,     7,     8,     3,    90,    70,
      71,    30,     1,    58,    20,    59,    60,    61,    62,    63,
       4,    31,    53,    54,    55,    56,    64,    21,    72,    59,
      60,    61,    62,    63,    73,    19,     9,    91,    22,    23,
      38,    39,    40,    41,    42,    43,    44,    46,    47,    48,
      49,    50,    83,    84,    28,    32,    34,    35,    37,    52,
      68,    74,    57,    85,    69,    75,    76,    77,    86,    81,
      78,    80,    82,    79,    99,    93,    88,    89,    97,     0,
      92,    87,   101,    95,    94,    96,   103,   100,    98,   102
};

static const yytype_int8 yycheck[] =
{
      11,     8,     8,     9,    21,    11,    12,    33,    10,    42,
      43,    27,    13,    30,    18,     3,     4,     5,     6,     7,
       0,    37,    41,    42,    43,    44,    14,    31,    45,     3,
       4,     5,     6,     7,    51,    31,    42,    39,    42,    43,
      22,    23,    24,    25,    26,    27,    28,    17,    18,    19,
      20,    21,    15,    16,    31,    34,    42,    42,    29,    40,
      32,    37,    40,    74,    32,    32,    32,    32,    79,    30,
      32,    31,    30,    37,    43,    32,    83,    84,    29,    -1,
      39,    80,    30,    38,    40,    38,    38,    98,    37,    39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    13,    46,    33,     0,     8,     9,    11,    12,    42,
      47,    48,    49,    50,    54,    59,    60,    61,    64,    31,
      18,    31,    42,    43,    56,    57,    58,    62,    31,    62,
      27,    37,    34,    47,    42,    42,    56,    29,    22,    23,
      24,    25,    26,    27,    28,    63,    17,    18,    19,    20,
      21,    55,    40,    41,    42,    43,    44,    40,    56,     3,
       4,     5,     6,     7,    14,    51,    52,    53,    32,    32,
      42,    43,    56,    56,    37,    32,    32,    32,    32,    37,
      31,    30,    30,    15,    16,    47,    47,    52,    62,    62,
      10,    39,    39,    32,    40,    38,    38,    29,    37,    43,
      47,    30,    39,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    49,    49,    49,
      50,    51,    51,    52,    52,    52,    52,    52,    53,    54,
      55,    55,    55,    55,    55,    56,    56,    57,    57,    57,
      58,    58,    58,    58,    59,    59,    59,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     1,     2,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     7,     3,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       2,     4,     4,     3,     4,     4,     4,     4,     4,     1,
       1,     7,    11,     3,     5,     5,     1,     1,     1,     1,
       1,     1,     1,     7
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: REPORT BRACKETOPEN stmtlist BRACKETCLOSE  */
#line 61 "lang.y"
                                                     { printf("program -> report { stmtlist }\n"); }
#line 1193 "lang.tab.c"
    break;

  case 3: /* stmtlist: stmt  */
#line 64 "lang.y"
                             { printf("stmtlist -> stmt\n"); }
#line 1199 "lang.tab.c"
    break;

  case 4: /* stmtlist: stmt stmtlist  */
#line 65 "lang.y"
                             { printf("stmtlist -> stmt stmtlist\n"); }
#line 1205 "lang.tab.c"
    break;

  case 5: /* stmt: simplstmt  */
#line 68 "lang.y"
                            { printf("stmt -> simplstmt\n"); }
#line 1211 "lang.tab.c"
    break;

  case 6: /* stmt: structstmt  */
#line 69 "lang.y"
                            { printf("stmt -> structstmt\n"); }
#line 1217 "lang.tab.c"
    break;

  case 7: /* simplstmt: declaration  */
#line 72 "lang.y"
                                  { printf("stmt -> declaration\n"); }
#line 1223 "lang.tab.c"
    break;

  case 8: /* simplstmt: assignstmt  */
#line 73 "lang.y"
                                  { printf("stmt -> assignstmt\n"); }
#line 1229 "lang.tab.c"
    break;

  case 9: /* simplstmt: iostmt  */
#line 74 "lang.y"
                                  { printf("stmt -> iostmt\n"); }
#line 1235 "lang.tab.c"
    break;

  case 10: /* declaration: IDENTIFIER COLON type  */
#line 77 "lang.y"
                                    { printf("declaration -> IDENTIFIER : type\n"); }
#line 1241 "lang.tab.c"
    break;

  case 11: /* type: type1  */
#line 80 "lang.y"
                            { printf("type -> type1\n"); }
#line 1247 "lang.tab.c"
    break;

  case 12: /* type: arraydecl  */
#line 81 "lang.y"
                            { printf("type -> arraydecl\n"); }
#line 1253 "lang.tab.c"
    break;

  case 13: /* type1: INT  */
#line 84 "lang.y"
                           { printf("type1 -> int\n"); }
#line 1259 "lang.tab.c"
    break;

  case 14: /* type1: REAL  */
#line 85 "lang.y"
                           { printf("type1 -> real\n"); }
#line 1265 "lang.tab.c"
    break;

  case 15: /* type1: STR  */
#line 86 "lang.y"
                           { printf("type1 -> str\n"); }
#line 1271 "lang.tab.c"
    break;

  case 16: /* type1: CHAR  */
#line 87 "lang.y"
                           { printf("type1 -> char\n"); }
#line 1277 "lang.tab.c"
    break;

  case 17: /* type1: BOOL  */
#line 88 "lang.y"
                           { printf("type1 -> bool\n"); }
#line 1283 "lang.tab.c"
    break;

  case 18: /* arraydecl: ARR OPEN type1 CLOSE SQBRACKETOPEN INTCONSTANT SQBRACKETCLOSE  */
#line 91 "lang.y"
                                                                          { printf("arraydecl -> arr ( type1 ) [ INTCONSTANT ]\n"); }
#line 1289 "lang.tab.c"
    break;

  case 19: /* assignstmt: IDENTIFIER EQ expression  */
#line 94 "lang.y"
                                      { printf("assignstmt -> IDENTIFIER = expression\n"); }
#line 1295 "lang.tab.c"
    break;

  case 20: /* operator: PLUS  */
#line 97 "lang.y"
                             { printf("operator -> +\n"); }
#line 1301 "lang.tab.c"
    break;

  case 21: /* operator: MINUS  */
#line 98 "lang.y"
                             { printf("operator -> -\n"); }
#line 1307 "lang.tab.c"
    break;

  case 22: /* operator: TIMES  */
#line 99 "lang.y"
                             { printf("operator -> *\n"); }
#line 1313 "lang.tab.c"
    break;

  case 23: /* operator: DIV  */
#line 100 "lang.y"
                             { printf("operator -> /\n"); }
#line 1319 "lang.tab.c"
    break;

  case 24: /* operator: MOD  */
#line 101 "lang.y"
                             { printf("operator -> %%\n"); }
#line 1325 "lang.tab.c"
    break;

  case 25: /* expression: term  */
#line 104 "lang.y"
                                          { printf("expression -> term\n"); }
#line 1331 "lang.tab.c"
    break;

  case 26: /* expression: term operator expression  */
#line 105 "lang.y"
                                          { printf("expression -> term operator expression\n"); }
#line 1337 "lang.tab.c"
    break;

  case 27: /* term: IDENTIFIER  */
#line 108 "lang.y"
                             { printf("term -> IDENTIFIER\n"); }
#line 1343 "lang.tab.c"
    break;

  case 28: /* term: INTCONSTANT  */
#line 109 "lang.y"
                             { printf("term -> INTCONSTANT\n"); }
#line 1349 "lang.tab.c"
    break;

  case 29: /* term: factor  */
#line 110 "lang.y"
                             { printf("term -> factor\n"); }
#line 1355 "lang.tab.c"
    break;

  case 30: /* factor: MINUS IDENTIFIER  */
#line 113 "lang.y"
                                     { printf("factor -> - IDENTIFIER\n"); }
#line 1361 "lang.tab.c"
    break;

  case 31: /* factor: IDENTIFIER SQBRACKETOPEN IDENTIFIER SQBRACKETCLOSE  */
#line 114 "lang.y"
                                                            { printf("factor -> IDENTIFIER [ IDENTIFIER ]\n"); }
#line 1367 "lang.tab.c"
    break;

  case 32: /* factor: IDENTIFIER SQBRACKETOPEN INTCONSTANT SQBRACKETCLOSE  */
#line 115 "lang.y"
                                                             { printf("factor -> IDENTIFIER [ INTCONSTANT ]\n"); }
#line 1373 "lang.tab.c"
    break;

  case 33: /* factor: OPEN expression CLOSE  */
#line 116 "lang.y"
                                     { printf("factor -> ( expression )\n"); }
#line 1379 "lang.tab.c"
    break;

  case 34: /* iostmt: READ OPEN IDENTIFIER CLOSE  */
#line 119 "lang.y"
                                          { printf("iostmt -> read (IDENTIFIER )\n"); }
#line 1385 "lang.tab.c"
    break;

  case 35: /* iostmt: WRITE OPEN IDENTIFIER CLOSE  */
#line 120 "lang.y"
                                          { printf("iostmt -> write ( IDENTIFIER )\n"); }
#line 1391 "lang.tab.c"
    break;

  case 36: /* iostmt: WRITE OPEN INTCONSTANT CLOSE  */
#line 121 "lang.y"
                                          { printf("iostmt -> write ( INTCONSTANT )\n"); }
#line 1397 "lang.tab.c"
    break;

  case 37: /* iostmt: WRITE OPEN STRINGCONSTANT CLOSE  */
#line 122 "lang.y"
                                          { printf("iostmt -> write ( STRINGCONSTANT )\n"); }
#line 1403 "lang.tab.c"
    break;

  case 38: /* iostmt: WRITE OPEN ENDL CLOSE  */
#line 123 "lang.y"
                                          { printf("iostmt -> write ( endl )\n"); }
#line 1409 "lang.tab.c"
    break;

  case 39: /* structstmt: ifstmt  */
#line 126 "lang.y"
                              { printf("structstmt -> ifstmt\n"); }
#line 1415 "lang.tab.c"
    break;

  case 40: /* structstmt: whilestmt  */
#line 127 "lang.y"
                              { printf("structstmt -> whilestmt\n"); }
#line 1421 "lang.tab.c"
    break;

  case 41: /* ifstmt: IF condition BEGIN_BLOCK COLON stmtlist END_BLOCK SEMICOLON  */
#line 130 "lang.y"
                                                                                                     { printf("ifstmt -> if condition begin : stmtlist end ;\n"); }
#line 1427 "lang.tab.c"
    break;

  case 42: /* ifstmt: IF condition BEGIN_BLOCK COLON stmtlist ELSE BEGIN_BLOCK COLON stmtlist END_BLOCK SEMICOLON  */
#line 131 "lang.y"
                                                                                                     { printf("ifstmt -> if condition begin : stmtlist else begin : stmtlist end ;\n"); }
#line 1433 "lang.tab.c"
    break;

  case 43: /* condition: expression RELATION expression  */
#line 134 "lang.y"
                                                                 { printf("condition -> expression RELATION expression\n"); }
#line 1439 "lang.tab.c"
    break;

  case 44: /* condition: expression RELATION expression AND condition  */
#line 135 "lang.y"
                                                                 { printf("condition -> expression RELATION expression and condition\n"); }
#line 1445 "lang.tab.c"
    break;

  case 45: /* condition: expression RELATION expression OR condition  */
#line 136 "lang.y"
                                                                 { printf("condition -> expression RELATION expression or condition\n"); }
#line 1451 "lang.tab.c"
    break;

  case 46: /* RELATION: BIGGEREQ  */
#line 139 "lang.y"
                              { printf("RELATION -> >=\n"); }
#line 1457 "lang.tab.c"
    break;

  case 47: /* RELATION: LESSEQ  */
#line 140 "lang.y"
                              { printf("RELATION -> <=\n"); }
#line 1463 "lang.tab.c"
    break;

  case 48: /* RELATION: BIGGER  */
#line 141 "lang.y"
                              { printf("RELATION -> >\n"); }
#line 1469 "lang.tab.c"
    break;

  case 49: /* RELATION: LESS  */
#line 142 "lang.y"
                              { printf("RELATION -> <\n"); }
#line 1475 "lang.tab.c"
    break;

  case 50: /* RELATION: EQQ  */
#line 143 "lang.y"
                              { printf("RELATION -> ==\n"); }
#line 1481 "lang.tab.c"
    break;

  case 51: /* RELATION: EQ  */
#line 144 "lang.y"
                              { printf("RELATION -> =\n"); }
#line 1487 "lang.tab.c"
    break;

  case 52: /* RELATION: NEQ  */
#line 145 "lang.y"
                              { printf("RELATION -> !=\n"); }
#line 1493 "lang.tab.c"
    break;

  case 53: /* whilestmt: WHILE condition BEGIN_BLOCK COLON stmtlist END_BLOCK SEMICOLON  */
#line 148 "lang.y"
                                                                           { printf("whilestmt -> while condition begin : stmtlist end ;\n"); }
#line 1499 "lang.tab.c"
    break;


#line 1503 "lang.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 152 "lang.y"


int yyerror(const char *s) {
    printf("%s\n",s);
    return 0;
}

extern FILE *yyin;

int main(int argc, char** argv) {
    if (argc > 1)
        yyin = fopen(argv[1], "r");
    if (!yyparse())
        fprintf(stderr, "\tOK\n");
}
