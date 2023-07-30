/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "syntax.y"

#include<stdio.h>
#include<stdlib.h>
#include "main.h"
#include "lex.yy.c"
Node* syntax_tree=NULL;         
Node* CreateTree(int type,int line,Node* ch0,Node* ch1,Node* ch2){
    if(ch0 == NULL)
        ch0=ch1, ch1=ch2, ch2=NULL;
    if(ch1 == NULL)
        ch1=ch2, ch2=NULL;              
    Node* node=NewNode();
    node->isTerminal=0;
    node->type=type;
    node->line=line;
    node->child=ch0;
    if(ch0 != NULL)
        ch0->next=ch1;
    if(ch1 != NULL)
        ch1->next=ch2;
    return node;
}
void AddChild(Node* node,Node* child){
    if(child == NULL)
        return;
    if(node->child == NULL)
        node->child=child;
    else{
        for(Node* i=node->child; i; i=i->next)
            if(i->next == NULL){
                i->next=child;
                break;
            }
    }
}

#line 107 "syntax.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMI = 258,
    COMMA = 259,
    ASSIGNOP = 260,
    PLUS = 261,
    MINUS = 262,
    STAR = 263,
    DIV = 264,
    AND = 265,
    OR = 266,
    DOT = 267,
    NOT = 268,
    LP = 269,
    RP = 270,
    LB = 271,
    RB = 272,
    LC = 273,
    RC = 274,
    RELOP = 275,
    TYPE = 276,
    STRUCT = 277,
    RETURN = 278,
    IF = 279,
    ELSE = 280,
    WHILE = 281,
    FLOAT = 282,
    INT = 283,
    ID = 284,
    LOWER_THAN_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "syntax.y"

    Node* type_node;

#line 194 "syntax.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

#define YYUNDEFTOK  2
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,    96,    99,   102,   106,   110,   116,   120,
     126,   130,   136,   142,   148,   149,   154,   159,   163,   170,
     175,   181,   185,   191,   196,   202,   203,   208,   212,   216,
     220,   226,   234,   242,   243,   248,   253,   257,   263,   267,
     273,   277,   281,   285,   289,   293,   298,   303,   309,   312,
     316,   322,   325,   329,   335,   338,   342,   348,   351,   357,
     360,   366,   369,   375,   378,   384,   388
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMI", "COMMA", "ASSIGNOP", "PLUS",
  "MINUS", "STAR", "DIV", "AND", "OR", "DOT", "NOT", "LP", "RP", "LB",
  "RB", "LC", "RC", "RELOP", "TYPE", "STRUCT", "RETURN", "IF", "ELSE",
  "WHILE", "FLOAT", "INT", "ID", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp1", "Exp2",
  "Exp3", "Exp4", "Exp5", "Exp6", "Exp7", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF (-100)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      22,  -100,   -17,    15,  -100,    22,     0,  -100,    12,    18,
    -100,  -100,  -100,  -100,    10,    56,     7,    49,    22,    39,
    -100,    47,    50,    22,  -100,    47,    58,    22,  -100,    47,
      64,    76,  -100,  -100,    65,    24,     9,    78,    79,  -100,
    -100,    68,  -100,    22,  -100,     6,     6,     6,     6,    71,
      72,  -100,  -100,    73,  -100,    69,    24,    46,  -100,    57,
      66,    70,    81,    11,    86,     6,  -100,    47,  -100,  -100,
    -100,    77,    90,     6,     6,    42,  -100,  -100,    67,     6,
       6,     6,     6,     6,     6,     6,     6,     6,  -100,  -100,
    -100,  -100,  -100,    80,    82,  -100,    94,    84,  -100,    83,
    -100,  -100,    57,    57,    66,    70,  -100,    81,    24,    24,
       6,  -100,  -100,    85,  -100,  -100,    24,  -100
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    10,    14,     0,     2,     4,     0,    11,    16,     0,
      13,     1,     3,     6,    17,     0,     8,     0,    33,     0,
       5,     0,     0,    33,     7,     0,     0,    33,    20,     0,
       0,    22,    17,     9,     0,    25,    38,     0,    36,    12,
      34,    23,    19,     0,    18,     0,     0,     0,     0,     0,
       0,    42,    41,    40,    28,     0,    25,    48,    51,    54,
      57,    59,    61,    63,     0,     0,    35,     0,    21,    49,
      50,     0,     0,     0,     0,     0,    24,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    27,    39,
      37,    43,    29,     0,     0,    44,    65,     0,    47,     0,
      52,    53,    55,    56,    58,    60,    64,    62,     0,     0,
       0,    45,    46,    30,    32,    66,     0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,  -100,    89,  -100,    87,     2,  -100,  -100,  -100,   -21,
    -100,    59,  -100,    88,    45,   -99,    41,  -100,    36,  -100,
    -100,   -40,    -8,    20,    21,    25,  -100,   -47,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    15,    25,     7,     9,    10,    16,
      17,    30,    31,    54,    55,    56,    26,    27,    37,    38,
      57,    58,    59,    60,    61,    62,    63,    64,    97
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    72,     6,    13,    36,    69,    70,     6,    41,   113,
     114,    21,     8,    45,    65,    11,    86,   117,    89,    46,
      47,    29,    87,    22,    19,    22,    93,    94,    96,    14,
     -15,    45,    99,    51,    52,    53,    18,    46,    47,   106,
     100,   101,    23,     1,     2,    29,    36,    48,    49,    45,
      50,    51,    52,    53,    28,    46,    47,    95,    78,    20,
       1,     2,    79,    96,    35,    80,    81,    23,    40,    51,
      52,    53,    82,    83,   102,   103,    32,    39,    34,    42,
      43,    66,    44,    67,    22,    73,    74,    75,    76,    88,
      84,    85,    91,    92,    12,   108,    98,   109,   110,   111,
     112,    77,    68,    90,   104,    24,   105,   115,    33,     0,
     116,     0,   107
};

static const yytype_int8 yycheck[] =
{
      47,    48,     0,     3,    25,    45,    46,     5,    29,   108,
     109,     4,    29,     7,     5,     0,     5,   116,    65,    13,
      14,    19,    11,    16,    14,    16,    73,    74,    75,    29,
      18,     7,    79,    27,    28,    29,    18,    13,    14,    86,
      80,    81,    18,    21,    22,    43,    67,    23,    24,     7,
      26,    27,    28,    29,    15,    13,    14,    15,    12,     3,
      21,    22,    16,   110,    23,     8,     9,    18,    27,    27,
      28,    29,     6,     7,    82,    83,    29,    19,    28,    15,
       4,     3,    17,     4,    16,    14,    14,    14,    19,     3,
      20,    10,    15,     3,     5,    15,    29,    15,     4,    15,
      17,    56,    43,    67,    84,    17,    85,   110,    21,    -1,
      25,    -1,    87
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    21,    22,    32,    33,    34,    36,    37,    29,    38,
      39,     0,    33,     3,    29,    35,    40,    41,    18,    14,
       3,     4,    16,    18,    44,    36,    47,    48,    15,    36,
      42,    43,    29,    35,    28,    47,    40,    49,    50,    19,
      47,    40,    15,     4,    17,     7,    13,    14,    23,    24,
      26,    27,    28,    29,    44,    45,    46,    51,    52,    53,
      54,    55,    56,    57,    58,     5,     3,     4,    42,    52,
      52,    58,    58,    14,    14,    14,    19,    45,    12,    16,
       8,     9,     6,     7,    20,    10,     5,    11,     3,    58,
      49,    15,     3,    58,    58,    15,    58,    59,    29,    58,
      52,    52,    53,    53,    54,    55,    58,    56,    15,    15,
       4,    15,    17,    46,    46,    59,    25,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    35,    35,
      36,    36,    37,    37,    38,    38,    39,    40,    40,    41,
      41,    42,    42,    43,    44,    45,    45,    46,    46,    46,
      46,    46,    46,    47,    47,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    52,
      52,    53,    53,    53,    54,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     0,     1,     1,     1,     4,     4,
       3,     3,     1,     2,     4,     0,     2,     2,     1,     3,
       5,     7,     5,     0,     2,     3,     1,     3,     1,     3,
       1,     1,     1,     3,     3,     4,     4,     3,     1,     2,
       2,     1,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 90 "syntax.y"
                     {
    syntax_tree=CreateTree(Unterm_Program,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)=syntax_tree;
}
#line 1560 "syntax.tab.c"
    break;

  case 3:
#line 96 "syntax.y"
                               {
    (yyval.type_node)=CreateTree(Unterm_ExtDefList,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
}
#line 1568 "syntax.tab.c"
    break;

  case 4:
#line 99 "syntax.y"
  {(yyval.type_node)=NULL;}
#line 1574 "syntax.tab.c"
    break;

  case 5:
#line 102 "syntax.y"
                                   {
    (yyval.type_node)=CreateTree(Unterm_ExtDef,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=0;
}
#line 1583 "syntax.tab.c"
    break;

  case 6:
#line 106 "syntax.y"
                 {
    (yyval.type_node)=CreateTree(Unterm_ExtDef,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
    (yyval.type_node)->subtype=1;
}
#line 1592 "syntax.tab.c"
    break;

  case 7:
#line 110 "syntax.y"
                          {
    (yyval.type_node)=CreateTree(Unterm_ExtDef,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=2;
}
#line 1601 "syntax.tab.c"
    break;

  case 8:
#line 116 "syntax.y"
                    {
    (yyval.type_node)=CreateTree(Unterm_ExtDecList,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 1610 "syntax.tab.c"
    break;

  case 9:
#line 120 "syntax.y"
                          {
    (yyval.type_node)=CreateTree(Unterm_ExtDecList,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=1;
}
#line 1619 "syntax.tab.c"
    break;

  case 10:
#line 126 "syntax.y"
                 {
    (yyval.type_node)=CreateTree(Unterm_Specifier,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 1628 "syntax.tab.c"
    break;

  case 11:
#line 130 "syntax.y"
                  {
    (yyval.type_node)=CreateTree(Unterm_Specifier,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=1;
}
#line 1637 "syntax.tab.c"
    break;

  case 12:
#line 136 "syntax.y"
                                              {
    (yyval.type_node)=CreateTree(Unterm_StructSpecifier,(yyloc).first_line,(yyvsp[-4].type_node),(yyvsp[-3].type_node),(yyvsp[-2].type_node));
    AddChild((yyval.type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=0;
}
#line 1648 "syntax.tab.c"
    break;

  case 13:
#line 142 "syntax.y"
             {
    (yyval.type_node)=CreateTree(Unterm_StructSpecifier,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
    (yyval.type_node)->subtype=1;
}
#line 1657 "syntax.tab.c"
    break;

  case 14:
#line 148 "syntax.y"
         {  (yyval.type_node)=NULL;    }
#line 1663 "syntax.tab.c"
    break;

  case 15:
#line 149 "syntax.y"
     {
    (yyval.type_node)=CreateTree(Unterm_OptTag,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
}
#line 1671 "syntax.tab.c"
    break;

  case 16:
#line 154 "syntax.y"
         {
    (yyval.type_node)=CreateTree(Unterm_Tag,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
}
#line 1679 "syntax.tab.c"
    break;

  case 17:
#line 159 "syntax.y"
            {
    (yyval.type_node)=CreateTree(Unterm_VarDec,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 1688 "syntax.tab.c"
    break;

  case 18:
#line 163 "syntax.y"
                   {
    (yyval.type_node)=CreateTree(Unterm_VarDec,(yyloc).first_line,(yyvsp[-3].type_node),(yyvsp[-2].type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=1;
}
#line 1698 "syntax.tab.c"
    break;

  case 19:
#line 170 "syntax.y"
                          {
    (yyval.type_node)=CreateTree(Unterm_FunDec,(yyloc).first_line,(yyvsp[-3].type_node),(yyvsp[-2].type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=0;
}
#line 1708 "syntax.tab.c"
    break;

  case 20:
#line 175 "syntax.y"
           {
    (yyval.type_node)=CreateTree(Unterm_FunDec,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=1;
}
#line 1717 "syntax.tab.c"
    break;

  case 21:
#line 181 "syntax.y"
                                 {
    (yyval.type_node)=CreateTree(Unterm_VarList,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=0;
}
#line 1726 "syntax.tab.c"
    break;

  case 22:
#line 185 "syntax.y"
           {
    (yyval.type_node)=CreateTree(Unterm_VarList,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=1;
}
#line 1735 "syntax.tab.c"
    break;

  case 23:
#line 191 "syntax.y"
                            {
    (yyval.type_node)=CreateTree(Unterm_ParamDec,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
}
#line 1743 "syntax.tab.c"
    break;

  case 24:
#line 196 "syntax.y"
                                {
    (yyval.type_node)=CreateTree(Unterm_CompSt,(yyloc).first_line,(yyvsp[-3].type_node),(yyvsp[-2].type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
}
#line 1752 "syntax.tab.c"
    break;

  case 25:
#line 202 "syntax.y"
           {    (yyval.type_node)=NULL;    }
#line 1758 "syntax.tab.c"
    break;

  case 26:
#line 203 "syntax.y"
                {
    (yyval.type_node)=CreateTree(Unterm_StmtList,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
}
#line 1766 "syntax.tab.c"
    break;

  case 27:
#line 208 "syntax.y"
                {
    (yyval.type_node)=CreateTree(Unterm_Stmt,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
    (yyval.type_node)->subtype=0;
}
#line 1775 "syntax.tab.c"
    break;

  case 28:
#line 212 "syntax.y"
         {
    (yyval.type_node)=CreateTree(Unterm_Stmt,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=1;
}
#line 1784 "syntax.tab.c"
    break;

  case 29:
#line 216 "syntax.y"
                  {
    (yyval.type_node)=CreateTree(Unterm_Stmt,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=2;
}
#line 1793 "syntax.tab.c"
    break;

  case 30:
#line 220 "syntax.y"
                    {
    (yyval.type_node)=CreateTree(Unterm_Stmt,(yyloc).first_line,(yyvsp[-4].type_node),(yyvsp[-3].type_node),(yyvsp[-2].type_node));
    AddChild((yyval.type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=3;
}
#line 1804 "syntax.tab.c"
    break;

  case 31:
#line 226 "syntax.y"
                              {
    (yyval.type_node)=CreateTree(Unterm_Stmt,(yyloc).first_line,(yyvsp[-6].type_node),(yyvsp[-5].type_node),(yyvsp[-4].type_node));
    AddChild((yyval.type_node),(yyvsp[-3].type_node));
    AddChild((yyval.type_node),(yyvsp[-2].type_node));
    AddChild((yyval.type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=4;
}
#line 1817 "syntax.tab.c"
    break;

  case 32:
#line 234 "syntax.y"
                       {
    (yyval.type_node)=CreateTree(Unterm_Stmt,(yyloc).first_line,(yyvsp[-4].type_node),(yyvsp[-3].type_node),(yyvsp[-2].type_node));
    AddChild((yyval.type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=5;
}
#line 1828 "syntax.tab.c"
    break;

  case 33:
#line 242 "syntax.y"
          { (yyval.type_node)=NULL;    }
#line 1834 "syntax.tab.c"
    break;

  case 34:
#line 243 "syntax.y"
              {
    (yyval.type_node)=CreateTree(Unterm_DefList,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
}
#line 1842 "syntax.tab.c"
    break;

  case 35:
#line 248 "syntax.y"
                             {
    (yyval.type_node)=CreateTree(Unterm_Def,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
}
#line 1850 "syntax.tab.c"
    break;

  case 36:
#line 253 "syntax.y"
              {
    (yyval.type_node)=CreateTree(Unterm_DecList,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 1859 "syntax.tab.c"
    break;

  case 37:
#line 257 "syntax.y"
                    {
    (yyval.type_node)=CreateTree(Unterm_DecList,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=1;
}
#line 1868 "syntax.tab.c"
    break;

  case 38:
#line 263 "syntax.y"
             {
    (yyval.type_node)=CreateTree(Unterm_Dec,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 1877 "syntax.tab.c"
    break;

  case 39:
#line 267 "syntax.y"
                      {
    (yyval.type_node)=CreateTree(Unterm_Dec,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=1;
}
#line 1886 "syntax.tab.c"
    break;

  case 40:
#line 273 "syntax.y"
          {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 1895 "syntax.tab.c"
    break;

  case 41:
#line 277 "syntax.y"
      {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=1;
}
#line 1904 "syntax.tab.c"
    break;

  case 42:
#line 281 "syntax.y"
        {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=2;
}
#line 1913 "syntax.tab.c"
    break;

  case 43:
#line 285 "syntax.y"
            {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=3;
}
#line 1922 "syntax.tab.c"
    break;

  case 44:
#line 289 "syntax.y"
           {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=4;
}
#line 1931 "syntax.tab.c"
    break;

  case 45:
#line 293 "syntax.y"
                {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-3].type_node),(yyvsp[-2].type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=5;
}
#line 1941 "syntax.tab.c"
    break;

  case 46:
#line 298 "syntax.y"
                 {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-3].type_node),(yyvsp[-2].type_node),(yyvsp[-1].type_node));
    AddChild((yyval.type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=6;
}
#line 1951 "syntax.tab.c"
    break;

  case 47:
#line 303 "syntax.y"
              {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=7;
}
#line 1960 "syntax.tab.c"
    break;

  case 48:
#line 309 "syntax.y"
            {
    (yyval.type_node)=(yyvsp[0].type_node);      
}
#line 1968 "syntax.tab.c"
    break;

  case 49:
#line 312 "syntax.y"
             {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
    (yyval.type_node)->subtype=8;
}
#line 1977 "syntax.tab.c"
    break;

  case 50:
#line 316 "syntax.y"
           {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-1].type_node),(yyvsp[0].type_node),NULL);
    (yyval.type_node)->subtype=9;
}
#line 1986 "syntax.tab.c"
    break;

  case 51:
#line 322 "syntax.y"
            {
    (yyval.type_node)=(yyvsp[0].type_node);
}
#line 1994 "syntax.tab.c"
    break;

  case 52:
#line 325 "syntax.y"
                 {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=10;
}
#line 2003 "syntax.tab.c"
    break;

  case 53:
#line 329 "syntax.y"
                {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=11;
}
#line 2012 "syntax.tab.c"
    break;

  case 54:
#line 335 "syntax.y"
            {
    (yyval.type_node)=(yyvsp[0].type_node);
}
#line 2020 "syntax.tab.c"
    break;

  case 55:
#line 338 "syntax.y"
                 {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=12;
}
#line 2029 "syntax.tab.c"
    break;

  case 56:
#line 342 "syntax.y"
                  {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=13;
}
#line 2038 "syntax.tab.c"
    break;

  case 57:
#line 348 "syntax.y"
            {
    (yyval.type_node)=(yyvsp[0].type_node);
}
#line 2046 "syntax.tab.c"
    break;

  case 58:
#line 351 "syntax.y"
                  {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=14;
}
#line 2055 "syntax.tab.c"
    break;

  case 59:
#line 357 "syntax.y"
            {
    (yyval.type_node)=(yyvsp[0].type_node);
}
#line 2063 "syntax.tab.c"
    break;

  case 60:
#line 360 "syntax.y"
                {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=15;
}
#line 2072 "syntax.tab.c"
    break;

  case 61:
#line 366 "syntax.y"
            {
    (yyval.type_node)=(yyvsp[0].type_node);
}
#line 2080 "syntax.tab.c"
    break;

  case 62:
#line 369 "syntax.y"
               {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=16;
}
#line 2089 "syntax.tab.c"
    break;

  case 63:
#line 375 "syntax.y"
           {
    (yyval.type_node)=(yyvsp[0].type_node);
}
#line 2097 "syntax.tab.c"
    break;

  case 64:
#line 378 "syntax.y"
                    {
    (yyval.type_node)=CreateTree(Unterm_Exp,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=17;
}
#line 2106 "syntax.tab.c"
    break;

  case 65:
#line 384 "syntax.y"
           {
    (yyval.type_node)=CreateTree(Unterm_Args,(yyloc).first_line,(yyvsp[0].type_node),NULL,NULL);
    (yyval.type_node)->subtype=0;
}
#line 2115 "syntax.tab.c"
    break;

  case 66:
#line 388 "syntax.y"
                 {
    (yyval.type_node)=CreateTree(Unterm_Args,(yyloc).first_line,(yyvsp[-2].type_node),(yyvsp[-1].type_node),(yyvsp[0].type_node));
    (yyval.type_node)->subtype=1;
}
#line 2124 "syntax.tab.c"
    break;


#line 2128 "syntax.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 394 "syntax.y"

void yyerror(const char* msg){
}
