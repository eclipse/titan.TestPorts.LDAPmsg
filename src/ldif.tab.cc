/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VERSION = 258,
     SEP = 259,
     DN = 260,
     COLON = 261,
     SAFE_STRING = 262,
     SAFE_BASE64_STRING = 263,
     GREATER = 264,
     SEMICOLON = 265,
     HYPHEN = 266,
     FLOAT_VAL = 267,
     INTEGER_VAL = 268,
     BISON_CONTROL = 269,
     BISON_TRUE = 270,
     BISON_FALSE = 271,
     CHANGETYPE = 272,
     ADD = 273,
     DELETE = 274,
     MODRDN = 275,
     MODDN = 276,
     NEWRDN = 277,
     DELETEOLDRDN = 278,
     ADD_COLON = 279,
     DELETE_COLON = 280,
     NEWSUPERIOR = 281,
     MODIFY = 282,
     REPLACE = 283,
     URL_STRING = 284,
     ZERO = 285,
     ONE = 286,
     LDAP_OID = 287,
     CHAR_ATTRIBUTE_TYPE = 288
   };
#endif
/* Tokens.  */
#define VERSION 258
#define SEP 259
#define DN 260
#define COLON 261
#define SAFE_STRING 262
#define SAFE_BASE64_STRING 263
#define GREATER 264
#define SEMICOLON 265
#define HYPHEN 266
#define FLOAT_VAL 267
#define INTEGER_VAL 268
#define BISON_CONTROL 269
#define BISON_TRUE 270
#define BISON_FALSE 271
#define CHANGETYPE 272
#define ADD 273
#define DELETE 274
#define MODRDN 275
#define MODDN 276
#define NEWRDN 277
#define DELETEOLDRDN 278
#define ADD_COLON 279
#define DELETE_COLON 280
#define NEWSUPERIOR 281
#define MODIFY 282
#define REPLACE 283
#define URL_STRING 284
#define ZERO 285
#define ONE 286
#define LDAP_OID 287
#define CHAR_ATTRIBUTE_TYPE 288




/* Copy the first part of user declarations.  */
#line 1 "ldif.y"

/******************************************************************************
* Copyright (c) 2000-2019 Ericsson Telecom AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v2.0
* which accompanies this distribution, and is available at
* https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
*
* Contributors:
* Endre Szalai
* Adam Delic
* Attila Balasko
* Csaba Feher
* Csaba Fehér
* Gabor Bettesch
* Gabor Szalai
* Gergely Futo
* Kristof Szabados
* Oliver Czerman
* Roland Gecse
* Tibor Szabo
* Zsolt Nandor Torok
* Zsolt Torpis
* Zsolt Török
******************************************************************************/
//
//  File:               ldif.y
//  Description:        BISON LDIF parser source code
//  Rev:                R9B
//  Prodnr:             CNL 113 385
// 
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "LDIF.hh"

extern int yylex();
extern void yyerror(const char *s);
extern void yyrestart(FILE* input_file);


int line_number = 0;
boolean error_recovery = false;
LDIF::LDIFData temporal_data;
LDIF::AttrValRecord temporal_AttrValRecord;
LDIF::LDIFControl temporal_Control;
LDIF::ChangeModifyData temporal_changemodifydata;
int AttrValRecord_Counter = 0;
int option_counter = 0;
int data_counter = 0;
int control_counter = 0;
int modification_counter = 0;
boolean erroneous;
boolean inner_resolve_env;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 45 "ldif.y"
{
	CHARSTRING *string_val;
}
/* Line 187 of yacc.c.  */
#line 211 "ldif.tab.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 224 "ldif.tab.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNRULES -- Number of states.  */
#define YYNSTATES  200

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,    12,    15,    17,    21,    24,
      26,    29,    31,    35,    38,    40,    45,    48,    49,    53,
      57,    62,    65,    67,    69,    72,    76,    79,    83,    89,
      95,   101,   103,   105,   106,   109,   110,   112,   114,   116,
     121,   125,   130,   134,   139,   144,   146,   149,   152,   155,
     157,   160,   162,   164,   167,   170,   174,   178,   181,   184,
     186,   188,   190,   192,   196,   200,   203,   205,   208,   217,
     226,   235,   244,   253,   255,   257,   259,   262,   266,   269,
     273,   276,   280,   282,   284,   286,   290,   294,   299,   300,
     304,   309,   313,   318,   322,   325,   329,   337,   344,   350,
     357,   364,   366,   368,   370,   372,   374,   377,   380
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      35,     0,    -1,    42,    36,    -1,    36,    -1,    38,    37,
      36,    -1,    38,    36,    -1,    38,    -1,    40,    37,    36,
      -1,    40,    36,    -1,    40,    -1,     4,    37,    -1,     4,
      -1,    44,     4,    39,    -1,    39,    49,    -1,    49,    -1,
      44,     4,    41,    54,    -1,    41,    45,    -1,    -1,     3,
      43,    37,    -1,     3,     1,    37,    -1,     3,    43,     1,
       4,    -1,     1,     4,    -1,    12,    -1,    13,    -1,     5,
       7,    -1,     5,     6,     8,    -1,     5,     1,    -1,     5,
       6,     1,    -1,    14,    48,    46,    47,     4,    -1,    14,
       1,    46,    47,     4,    -1,    14,    48,    46,    47,     1,
      -1,    15,    -1,    16,    -1,    -1,     6,    50,    -1,    -1,
      12,    -1,    13,    -1,    32,    -1,    51,     6,    50,     4,
      -1,    51,     6,     4,    -1,     1,     6,    50,     4,    -1,
       1,     6,     4,    -1,    51,     1,    50,     4,    -1,    51,
       6,     1,     4,    -1,     7,    -1,     6,     8,    -1,     9,
      29,    -1,    52,    53,    -1,    52,    -1,     1,    53,    -1,
      48,    -1,    33,    -1,    10,    33,    -1,    10,    13,    -1,
      53,    10,    13,    -1,    53,    10,    33,    -1,    10,     1,
      -1,    17,    55,    -1,    56,    -1,    58,    -1,    64,    -1,
      59,    -1,    18,     4,    57,    -1,    18,     4,     1,    -1,
      57,    49,    -1,    49,    -1,    19,     4,    -1,    60,     4,
      61,     4,    23,    62,     4,    63,    -1,    60,     1,    61,
       4,    23,    62,     4,    63,    -1,    60,     4,    61,     1,
      23,    62,     4,    63,    -1,    60,     4,    61,     4,     1,
      62,     4,    63,    -1,    60,     4,    61,     4,    23,    62,
       1,    63,    -1,    20,    -1,    21,    -1,     1,    -1,    22,
       7,    -1,    22,     6,     8,    -1,     1,     7,    -1,     1,
       6,     7,    -1,    22,     1,    -1,    22,     6,     1,    -1,
      30,    -1,    31,    -1,     1,    -1,    26,     7,     4,    -1,
      26,    33,     4,    -1,    26,     6,     8,     4,    -1,    -1,
      26,     1,     4,    -1,    26,     6,     1,     4,    -1,     1,
       7,     4,    -1,     1,     6,     8,     4,    -1,    27,     4,
      65,    -1,    27,     4,    -1,    27,     1,    65,    -1,    65,
      67,    66,     4,    68,    11,     4,    -1,    67,    66,     4,
      68,    11,     4,    -1,     1,     4,    68,    11,     4,    -1,
      67,    66,     1,    68,    11,     4,    -1,    67,    66,     4,
      68,     1,     4,    -1,    51,    -1,     1,    -1,    24,    -1,
      25,    -1,    28,    -1,     1,     6,    -1,    68,    49,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    63,    70,    71,    72,    73,    74,    75,
      79,    80,    84,    88,    93,   101,   105,   111,   118,   124,
     130,   136,   145,   149,   156,   243,   253,   265,   280,   285,
     295,   308,   312,   317,   323,   340,   346,   350,   354,   361,
     362,   367,   379,   391,   397,   408,   490,   496,   504,   509,
     514,   527,   533,   542,   547,   552,   557,   562,   575,   583,
     584,   585,   586,   590,   591,   606,   612,   622,   630,   633,
     643,   653,   666,   681,   686,   691,   706,   713,   720,   730,
     740,   751,   765,   770,   775,   789,   796,   803,   811,   816,
     828,   840,   853,   869,   870,   875,   886,   892,   898,   904,
     913,   928,   935,   951,   956,   961,   966,   982,   987
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VERSION", "SEP", "DN", "COLON",
  "SAFE_STRING", "SAFE_BASE64_STRING", "GREATER", "SEMICOLON", "HYPHEN",
  "FLOAT_VAL", "INTEGER_VAL", "BISON_CONTROL", "BISON_TRUE", "BISON_FALSE",
  "CHANGETYPE", "ADD", "DELETE", "MODRDN", "MODDN", "NEWRDN",
  "DELETEOLDRDN", "ADD_COLON", "DELETE_COLON", "NEWSUPERIOR", "MODIFY",
  "REPLACE", "URL_STRING", "ZERO", "ONE", "LDAP_OID",
  "CHAR_ATTRIBUTE_TYPE", "$accept", "ldif_file", "ldif_end",
  "optional_separators", "ldif_attrval_record", "attrval_specs",
  "ldif_change_record", "controls", "version_spec", "version_number",
  "dn_spec", "control", "control_mid", "control_end", "ldap_oid",
  "attrval_spec", "value_spec", "AttributeDescription", "AttributeType",
  "options", "changerecord", "changerecord_end", "change_add",
  "change_add_end", "change_delete", "change_moddn", "change_moddn_start",
  "change_moddn_middle", "zero_or_one", "change_moddn_end",
  "change_modify", "mod_spec", "mod_spec_middle", "mod_spec_start",
  "optional_attrval_spec", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    35,    36,    36,    36,    36,    36,    36,
      37,    37,    38,    39,    39,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    44,    44,    45,    45,
      45,    46,    46,    46,    47,    47,    48,    48,    48,    49,
      49,    49,    49,    49,    49,    50,    50,    50,    51,    51,
      51,    52,    52,    53,    53,    53,    53,    53,    54,    55,
      55,    55,    55,    56,    56,    57,    57,    58,    59,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    64,    65,    65,    65,    65,
      65,    66,    66,    67,    67,    67,    67,    68,    68
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     2,     1,     3,     2,     1,
       2,     1,     3,     2,     1,     4,     2,     0,     3,     3,
       4,     2,     1,     1,     2,     3,     2,     3,     5,     5,
       5,     1,     1,     0,     2,     0,     1,     1,     1,     4,
       3,     4,     3,     4,     4,     1,     2,     2,     2,     1,
       2,     1,     1,     2,     2,     3,     3,     2,     2,     1,
       1,     1,     1,     3,     3,     2,     1,     2,     8,     8,
       8,     8,     8,     1,     1,     1,     2,     3,     2,     3,
       2,     3,     1,     1,     1,     3,     3,     4,     0,     3,
       4,     3,     4,     3,     2,     3,     7,     6,     5,     6,
       6,     1,     1,     1,     1,     1,     2,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     3,     6,     9,     0,     0,
      21,     0,    22,    23,     0,    26,     0,    24,     1,    11,
       5,     0,     8,     0,     2,     0,    19,     0,    18,    27,
      25,    10,     4,     7,     0,    36,    37,    38,    52,     0,
       0,    51,    14,     0,    49,    20,     0,     0,    50,    13,
       0,     0,    16,    15,     0,     0,    48,    42,     0,    45,
       0,     0,    57,    54,    53,     0,    33,    33,    75,     0,
       0,    73,    74,     0,    58,    59,    60,    62,     0,    61,
       0,     0,    40,     0,    46,    47,    41,    55,    56,    31,
      32,    35,    35,     0,    67,     0,     0,     0,     0,    43,
      44,    39,     0,     0,     0,    64,    66,     0,     0,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,    34,
      29,    30,    28,    65,   108,   106,     0,     0,   102,   101,
       0,     0,    78,    80,     0,    76,     0,     0,     0,     0,
       0,   108,   108,    79,    81,    77,     0,     0,     0,     0,
       0,   107,   108,     0,     0,    84,    82,    83,     0,     0,
       0,     0,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    99,   100,    97,     0,     0,    69,    70,
      71,    72,    68,    96,     0,     0,     0,     0,     0,     0,
       0,    91,    89,     0,     0,    85,    86,    92,    90,    87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,    21,     6,    39,     7,    40,     8,    14,
       9,    52,    91,   103,    41,   151,    61,    43,    44,    48,
      53,    74,    75,   107,    76,    77,    78,   117,   158,   178,
      79,   112,   130,   113,   139
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
     180,     9,    27,   161,    67,   -54,    92,    92,    72,    84,
     -54,   106,   -54,   -54,   145,   -54,   153,   -54,   -54,   106,
     -54,    72,   -54,    72,   -54,    10,   -54,   201,   -54,   -54,
     -54,   -54,   -54,   -54,   163,   -54,   -54,   -54,   -54,     3,
     146,   -54,   -54,    55,   203,   -54,   173,    20,   204,   -54,
      73,   105,   -54,   -54,   187,   144,   204,   -54,   207,   -54,
     188,   212,   -54,   -54,   -54,    -1,   122,   122,   -54,   214,
     215,   -54,   -54,   183,   -54,   -54,   -54,   -54,   194,   -54,
     216,   217,   -54,   218,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   205,   205,    59,   -54,    94,    89,    19,    19,   -54,
     -54,   -54,   187,   219,   196,   163,   -54,     5,   182,   -54,
     -54,   -54,   103,    68,   111,   114,   164,   220,   198,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   221,    68,   203,   -54,
     200,   222,   -54,   -54,   156,   -54,   208,   209,    25,    18,
     224,   -54,   -54,   -54,   -54,   -54,    24,    24,    24,    24,
     226,   -54,   -54,    33,    46,   -54,   -54,   -54,   229,   230,
     231,   202,   -54,    51,   232,   168,   233,   129,   129,   129,
     129,   129,   234,   -54,   -54,   -54,   169,    69,   -54,   -54,
     -54,   -54,   -54,   -54,   235,   236,   237,   158,   238,   240,
     241,   -54,   -54,   242,   243,   -54,   -54,   -54,   -54,   -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   135,   133,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   159,   147,   175,   -25,   -53,   -40,   -54,   206,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   150,    60,    21,
     -54,   155,   125,    98,   -43
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -96
static const yytype_int16 yytable[] =
{
      42,    80,    83,   -12,    34,   -63,    34,   -12,   -12,   -63,
     -63,    34,    87,    10,    49,    35,    36,    35,    36,    34,
     115,    62,    35,    36,   -17,   155,   148,   -17,    11,   150,
      35,    36,    88,    63,    34,    37,    38,    37,    38,    12,
      13,   116,    37,    38,   164,    35,    36,   165,   149,   119,
      37,    38,    34,    64,   156,   157,    54,   166,    35,    36,
     105,    55,   172,    35,    36,    37,    38,    18,   106,   128,
     186,    35,    36,   129,    66,   187,   188,     3,    37,    38,
      35,    36,   123,    37,    38,    35,    36,   129,    25,   -94,
     108,    37,    38,   -94,   -94,   108,    19,     3,   153,   154,
      37,    38,   189,   -95,   126,    37,    68,   -95,   -95,   163,
      19,   -93,   126,   109,   110,   -93,   -93,   111,   109,   110,
     131,   132,   111,    69,    70,    71,    72,   109,   110,   -88,
     176,   111,    73,   -88,   -88,   109,   110,    89,    90,   111,
      23,    20,    22,    24,    26,    81,    27,    28,    82,    19,
      58,    59,    31,    60,    29,   177,    32,   144,    33,   193,
      50,    30,    15,    51,   145,   133,   194,    16,    17,    46,
     134,   135,   174,    47,    46,   184,   185,    57,    47,    58,
      59,     1,    60,     2,    95,     3,   124,    96,   125,   179,
     180,   181,   182,    58,    59,    97,    60,   121,    98,   137,
     122,   141,   138,   170,   142,    45,   171,   159,   160,   161,
     127,   102,   127,    47,    65,    84,    86,    85,    93,    94,
      99,   100,   101,   120,   136,    67,    92,   125,   152,   143,
     162,   146,   147,   167,   168,   169,   173,   175,   183,   104,
     191,   192,   195,   190,   196,   197,   198,   199,   118,     0,
      56,   114,   140
};

static const yytype_int16 yycheck[] =
{
      25,    54,    55,     0,     1,     0,     1,     4,     5,     4,
       5,     1,    13,     4,    39,    12,    13,    12,    13,     1,
       1,     1,    12,    13,    14,     1,     1,    17,     1,    11,
      12,    13,    33,    13,     1,    32,    33,    32,    33,    12,
      13,    22,    32,    33,    11,    12,    13,     1,    23,   102,
      32,    33,     1,    33,    30,    31,     1,    11,    12,    13,
       1,     6,    11,    12,    13,    32,    33,     0,    93,     1,
       1,    12,    13,   113,     1,     6,     7,     5,    32,    33,
      12,    13,   107,    32,    33,    12,    13,   127,     4,     0,
       1,    32,    33,     4,     5,     1,     4,     5,   141,   142,
      32,    33,    33,     0,     1,    32,     1,     4,     5,   152,
       4,     0,     1,    24,    25,     4,     5,    28,    24,    25,
       6,     7,    28,    18,    19,    20,    21,    24,    25,     0,
       1,    28,    27,     4,     5,    24,    25,    15,    16,    28,
       7,     6,     7,     8,    11,     1,     1,    14,     4,     4,
       6,     7,    19,     9,     1,    26,    21,     1,    23,     1,
      14,     8,     1,    17,     8,     1,     8,     6,     7,     6,
       6,     7,     4,    10,     6,     6,     7,     4,    10,     6,
       7,     1,     9,     3,     1,     5,     4,     4,     6,   168,
     169,   170,   171,     6,     7,     1,     9,     1,     4,     1,
       4,     1,     4,     1,     4,     4,     4,   147,   148,   149,
     112,     6,   114,    10,    10,     8,     4,    29,     4,     4,
       4,     4,     4,     4,     4,    50,    67,     6,     4,     7,
       4,    23,    23,     4,     4,     4,     4,     4,     4,    92,
       4,     4,     4,     8,     4,     4,     4,     4,    98,    -1,
      44,    96,   127
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     5,    35,    36,    38,    40,    42,    44,
       4,     1,    12,    13,    43,     1,     6,     7,     0,     4,
      36,    37,    36,    37,    36,     4,    37,     1,    37,     1,
       8,    37,    36,    36,     1,    12,    13,    32,    33,    39,
      41,    48,    49,    51,    52,     4,     6,    10,    53,    49,
      14,    17,    45,    54,     1,     6,    53,     4,     6,     7,
       9,    50,     1,    13,    33,    10,     1,    48,     1,    18,
      19,    20,    21,    27,    55,    56,    58,    59,    60,    64,
      50,     1,     4,    50,     8,    29,     4,    13,    33,    15,
      16,    46,    46,     4,     4,     1,     4,     1,     4,     4,
       4,     4,     6,    47,    47,     1,    49,    57,     1,    24,
      25,    28,    65,    67,    65,     1,    22,    61,    61,    50,
       4,     1,     4,    49,     4,     6,     1,    67,     1,    51,
      66,     6,     7,     1,     6,     7,     4,     1,     4,    68,
      66,     1,     4,     7,     1,     8,    23,    23,     1,    23,
      11,    49,     4,    68,    68,     1,    30,    31,    62,    62,
      62,    62,     4,    68,    11,     1,    11,     4,     4,     4,
       1,     4,    11,     4,     4,     4,     1,    26,    63,    63,
      63,    63,    63,     4,     6,     7,     1,     6,     7,    33,
       8,     4,     4,     1,     8,     4,     4,     4,     4,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 64 "ldif.y"
    {
    temporal_data.version() = OPTIONAL<INTEGER>(OMIT_VALUE);
  ;}
    break;

  case 13:
#line 89 "ldif.y"
    { 
      temporal_data.datalist()[data_counter-1].data().content()
        [AttrValRecord_Counter++] = temporal_AttrValRecord;
    ;}
    break;

  case 14:
#line 94 "ldif.y"
    {
      temporal_data.datalist()[data_counter-1].data().content()
        [AttrValRecord_Counter++] = temporal_AttrValRecord;
    ;}
    break;

  case 16:
#line 106 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .controllist()[control_counter++] = temporal_Control;
    ;}
    break;

  case 17:
#line 111 "ldif.y"
    {
       temporal_data.datalist()[data_counter-1].data().change()
         .controllist().set_size(0);
    ;}
    break;

  case 18:
#line 119 "ldif.y"
    {
       *((yyvsp[(2) - (3)].string_val)) == CHARSTRING("1") ? temporal_data.version() = 1 
         : temporal_data.version() = OPTIONAL<INTEGER>(OMIT_VALUE);
       delete (yyvsp[(2) - (3)].string_val);
    ;}
    break;

  case 19:
#line 125 "ldif.y"
    {
       TTCN_warning("Version error at line %d",line_number);
       error_recovery = false;
       erroneous = true;
    ;}
    break;

  case 20:
#line 131 "ldif.y"
    {
       TTCN_warning("Version error at line %d",line_number);
       erroneous = true;
       delete (yyvsp[(2) - (4)].string_val);
    ;}
    break;

  case 21:
#line 137 "ldif.y"
    {
       TTCN_warning("Version error at line %d",line_number);
       error_recovery = false;
       erroneous = true;
    ;}
    break;

  case 22:
#line 146 "ldif.y"
    {
       (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 23:
#line 150 "ldif.y"
    {
       (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 24:
#line 157 "ldif.y"
    {
       AttrValRecord_Counter = 0;
       modification_counter = 0;
       control_counter = 0;
       option_counter = 0;



       if(!inner_resolve_env)
       {
         temporal_data.datalist()[data_counter++].dn__string()
           = *((yyvsp[(2) - (2)].string_val));
       }else{
         CHARSTRING temp_char = CHARSTRING(*((yyvsp[(2) - (2)].string_val)));
         int index = 0;
         int start_pos = 0;
         int char_length = temp_char.lengthof();

         /*search for the first '$'*/
         for(; index < char_length && temp_char[index] != '$'; index++){}

         /*create the charstring from string till first '$'*/
         temporal_data.datalist()[data_counter].dn__string()
            = substr(temp_char,0,index);

         /*If there is some possible environment variable*/
         while(index < char_length)
         {
           start_pos = index++;
           boolean bracket= false;
           unsigned int temp_ascii = char2int(temp_char[index]);
           char *env_val = NULL;
           // the first character of the id shall be a letter
           if ((temp_ascii >= 65 && temp_ascii <= 90) ||     /*A..Z*/
               (temp_ascii >= 97 && temp_ascii <= 122) ||      /*a..z*/
               temp_ascii == 123) /* { */
           {
             do
             {/*Search the full environment variable*/
               if(temp_ascii == 123 /* { */) bracket=true;
               else env_val = mputc(env_val, (char)temp_ascii);
               index++;
               if(index < char_length)
                 temp_ascii = char2int(temp_char[index]);
               else
                 temp_ascii = 0;
             } while ((temp_ascii >= 65 && temp_ascii <= 90) ||  /*A..Z*/
                      (temp_ascii >= 97 && temp_ascii <= 122) || /*a..z*/
                      (temp_ascii >= 48 && temp_ascii <= 57) ||  /*0..9*/
                       temp_ascii == 95);                        /*_   */
             if( env_val && (!bracket || temp_ascii == 125)){
               char* temp = getenv((const char*)env_val);
               if(bracket) index++; /* skip closing bracket */
               if(temp == NULL)
               {/*Environment variable not found. store as $something*/
                 TTCN_warning("%s could not be resolved",(const char*)(env_val));
                 temporal_data.datalist()[data_counter].dn__string()
                   = temporal_data.datalist()[data_counter].dn__string()
                     + substr(temp_char,start_pos,index-start_pos);
               }
               else
               {/*replace environment variable with its value*/
                 temporal_data.datalist()[data_counter].dn__string()
                   = temporal_data.datalist()[data_counter].dn__string()
                     + temp;
               }
               start_pos = index;
               Free(env_val);
             }
           }
           /*search for the next '$'*/
           for(; index < char_length && temp_char[index] != '$'; index++){}

           if(start_pos < char_length)
             /*complete the charstring from string till next '$'*/
             temporal_data.datalist()[data_counter].dn__string()
               = temporal_data.datalist()[data_counter].dn__string()
                 + substr(temp_char,start_pos,index-start_pos);
         }
         data_counter++;
       }



       delete (yyvsp[(2) - (2)].string_val);
    ;}
    break;

  case 25:
#line 244 "ldif.y"
    {
       AttrValRecord_Counter = 0;
       modification_counter = 0;
       control_counter = 0;
       option_counter = 0;
       temporal_data.datalist()[data_counter++].dn__string() 
         = *((yyvsp[(3) - (3)].string_val));
       delete (yyvsp[(3) - (3)].string_val);
    ;}
    break;

  case 26:
#line 254 "ldif.y"
    {
       TTCN_warning("Wrong format for the dn at line %d",line_number);
       error_recovery = false;
       AttrValRecord_Counter = 0;
       modification_counter = 0;
       control_counter = 0;
       option_counter = 0;
       temporal_data.datalist()[data_counter++].dn__string() 
         = "ERROR";
       erroneous = true;
    ;}
    break;

  case 27:
#line 266 "ldif.y"
    {
       TTCN_warning("Wrong format for the dn at line %d",line_number);
       error_recovery = false;
       AttrValRecord_Counter = 0;
       modification_counter = 0;
       control_counter = 0;
       option_counter = 0;
       temporal_data.datalist()[data_counter++].dn__string() 
         = "ERROR";
       erroneous = true;
    ;}
    break;

  case 28:
#line 281 "ldif.y"
    {
       temporal_Control.ldapoid() = *((yyvsp[(2) - (5)].string_val));
       delete (yyvsp[(2) - (5)].string_val);
    ;}
    break;

  case 29:
#line 286 "ldif.y"
    {
       if(!error_recovery)
       {
         TTCN_warning("ldap_oid error at line %d",line_number);
         error_recovery = true;
       }
       temporal_Control.ldapoid() = "0";
       erroneous = true;
    ;}
    break;

  case 30:
#line 296 "ldif.y"
    {
       if(!error_recovery)
       {
         TTCN_warning("line number %d contains more than one data", line_number);
         error_recovery = true;
       }
       temporal_Control.ldapoid() = "0";
       erroneous = true;
    ;}
    break;

  case 31:
#line 309 "ldif.y"
    {
       temporal_Control.criticality() = true;
    ;}
    break;

  case 32:
#line 313 "ldif.y"
    {
       temporal_Control.criticality() = false;
    ;}
    break;

  case 33:
#line 317 "ldif.y"
    {
       temporal_Control.criticality() = OPTIONAL<BOOLEAN>(OMIT_VALUE);
    ;}
    break;

  case 34:
#line 324 "ldif.y"
    {
       if (temporal_AttrValRecord.attributevalue()().safe__string().ispresent()){
        temporal_Control.controlvalue() = 
          OCTETSTRING(temporal_AttrValRecord.attributevalue()().safe__string().lengthof(),
                      (const unsigned char*)(const char*)temporal_AttrValRecord.attributevalue()().safe__string());
       }else if (temporal_AttrValRecord.attributevalue()().base64__string().ispresent()){
        temporal_Control.controlvalue() = 
          OCTETSTRING(temporal_AttrValRecord.attributevalue()().base64__string().lengthof(),
                      (const unsigned char*)(const char*)temporal_AttrValRecord.attributevalue()().base64__string());
       }else{
        temporal_Control.controlvalue() = 
          OCTETSTRING(temporal_AttrValRecord.attributevalue()().url().lengthof(),
                      (const unsigned char*)(const char*)temporal_AttrValRecord.attributevalue()().url());
       }
    ;}
    break;

  case 35:
#line 340 "ldif.y"
    {
       temporal_Control.controlvalue() = OPTIONAL<OCTETSTRING>(OMIT_VALUE);
    ;}
    break;

  case 36:
#line 347 "ldif.y"
    {
       (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 37:
#line 351 "ldif.y"
    {
       (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 38:
#line 355 "ldif.y"
    {
       (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 40:
#line 363 "ldif.y"
    {
      temporal_AttrValRecord.attributevalue()().safe__string()
        = "";
    ;}
    break;

  case 41:
#line 368 "ldif.y"
    {
      if(!error_recovery){
        TTCN_warning("Attribute error at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.attributetype() = CHARSTRING("ERROR");
      temporal_AttrValRecord.optionlist().set_size(0);
      temporal_AttrValRecord.attributevalue()().safe__string()
         = CHARSTRING("ERROR");
      erroneous = true;
    ;}
    break;

  case 42:
#line 380 "ldif.y"
    {
      if(!error_recovery){
        TTCN_warning("Attribute error at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.attributetype() = CHARSTRING("ERROR");
      temporal_AttrValRecord.optionlist().set_size(0);
      temporal_AttrValRecord.attributevalue()().safe__string()
         = CHARSTRING("ERROR");
      erroneous = true;
    ;}
    break;

  case 43:
#line 392 "ldif.y"
    {
       TTCN_warning("Attribute must be separated from value with colon at line %d",line_number);
       error_recovery = false;
       erroneous = true;
    ;}
    break;

  case 44:
#line 398 "ldif.y"
    {
       TTCN_warning("Value error at line %d",line_number);
       error_recovery = false;
       temporal_AttrValRecord.attributevalue()().safe__string() 
         = CHARSTRING("ERROR");
       erroneous = true;
    ;}
    break;

  case 45:
#line 409 "ldif.y"
    {


       if(!inner_resolve_env)
       {
         temporal_AttrValRecord.attributevalue()().safe__string()
           = CHARSTRING(*((yyvsp[(1) - (1)].string_val)));
       }else{
         CHARSTRING temp_char = CHARSTRING(*((yyvsp[(1) - (1)].string_val)));
         int index = 0;
         int start_pos = 0;
         int char_length = temp_char.lengthof();

         /*search for the first '$'*/
         for(; index < char_length && temp_char[index] != '$'; index++){}

         /*create the charstring from string till first '$'*/
         temporal_AttrValRecord.attributevalue()().safe__string()
            = substr(temp_char,0,index);

         /*If there is some possible environment variable*/
         while(index < char_length)
         {
           start_pos = index++;
           unsigned int temp_ascii = char2int(temp_char[index]);
           char *env_val = NULL;
           bool bracket = false;
           /*The first character of the id shall be a letter*/
           if ((temp_ascii >= 65 && temp_ascii <= 90) ||     /*A..Z*/
               (temp_ascii >= 97 && temp_ascii <= 122) ||      /*a..z*/
               (temp_ascii == 123)) /* { */
           {
             do
             {/*Search the full environment variable*/
               if(temp_ascii == 123 /* { */) bracket=true;
               else env_val = mputc(env_val, (char)temp_ascii);
               index++;
               if(index < char_length)
                 temp_ascii = char2int(temp_char[index]);
               else
                 temp_ascii = 0;
             } while ((temp_ascii >= 65 && temp_ascii <= 90) ||  /*A..Z*/
                      (temp_ascii >= 97 && temp_ascii <= 122) || /*a..z*/
                      (temp_ascii >= 48 && temp_ascii <= 57) ||  /*0..9*/
                       temp_ascii == 95);                        /*_   */
             if( env_val && (!bracket || temp_ascii == 125)){
               char* temp = getenv((const char*)env_val);
               if(bracket) index++; /* skip closing bracket */
               if(temp == NULL)
               {/*Environment variable not found. store as $something*/
                 TTCN_warning("%s could not be resolved",(const char*)(env_val));
                 temporal_AttrValRecord.attributevalue()().safe__string()
                   = temporal_AttrValRecord.attributevalue()().safe__string()
                     + substr(temp_char,start_pos,index-start_pos);
               }
               else
               {/*replace environment variable with its value*/
                 temporal_AttrValRecord.attributevalue()().safe__string()
                   = temporal_AttrValRecord.attributevalue()().safe__string()
                     + temp;
               }
               start_pos = index;
               Free(env_val);
             }
           }
           /*search for the next '$'*/
           for(; index < char_length && temp_char[index] != '$'; index++){}

           if(start_pos < char_length)
             /*complete the charstring from string till next '$'*/
             temporal_AttrValRecord.attributevalue()().safe__string()
               = temporal_AttrValRecord.attributevalue()().safe__string()
                 + substr(temp_char,start_pos,index-start_pos);
         }
       }




       delete (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 46:
#line 491 "ldif.y"
    {
       temporal_AttrValRecord.attributevalue()().base64__string() 
         = *((yyvsp[(2) - (2)].string_val));
       delete (yyvsp[(2) - (2)].string_val);
    ;}
    break;

  case 47:
#line 497 "ldif.y"
    {
       temporal_AttrValRecord.attributevalue()().url() = *((yyvsp[(2) - (2)].string_val));
       delete (yyvsp[(2) - (2)].string_val);
    ;}
    break;

  case 48:
#line 505 "ldif.y"
    {
      temporal_AttrValRecord.attributetype() = *((yyvsp[(1) - (2)].string_val));
      delete (yyvsp[(1) - (2)].string_val);
    ;}
    break;

  case 49:
#line 510 "ldif.y"
    {
      temporal_AttrValRecord.attributetype() = *((yyvsp[(1) - (1)].string_val));
      delete (yyvsp[(1) - (1)].string_val);
    ;}
    break;

  case 50:
#line 515 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Attribute error at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.attributetype() = CHARSTRING("ERROR");
      erroneous = true;
    ;}
    break;

  case 51:
#line 528 "ldif.y"
    {
      (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
      option_counter = 0;
      temporal_AttrValRecord.optionlist().set_size(0);
    ;}
    break;

  case 52:
#line 534 "ldif.y"
    {
      (yyval.string_val) = (yyvsp[(1) - (1)].string_val);
      option_counter = 0;
      temporal_AttrValRecord.optionlist().set_size(0);
    ;}
    break;

  case 53:
#line 543 "ldif.y"
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *((yyvsp[(2) - (2)].string_val));
      delete (yyvsp[(2) - (2)].string_val);
    ;}
    break;

  case 54:
#line 548 "ldif.y"
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *((yyvsp[(2) - (2)].string_val));
      delete (yyvsp[(2) - (2)].string_val);
    ;}
    break;

  case 55:
#line 553 "ldif.y"
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *((yyvsp[(3) - (3)].string_val));
      delete (yyvsp[(3) - (3)].string_val);
    ;}
    break;

  case 56:
#line 558 "ldif.y"
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *((yyvsp[(3) - (3)].string_val));
      delete (yyvsp[(3) - (3)].string_val);
    ;}
    break;

  case 57:
#line 563 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong option syntax at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.optionlist()[option_counter++] = "ERROR";
      erroneous = true;
    ;}
    break;

  case 58:
#line 576 "ldif.y"
    {
      if(error_recovery)
        error_recovery = false;
    ;}
    break;

  case 64:
#line 592 "ldif.y"
    {
       if(!error_recovery)
       {
         TTCN_warning("Add must be followed by at least 1 attribute:value "
           "pair at line %d",line_number);
         error_recovery = true;
       }
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changeadd().set_size(0);
       erroneous = true;
    ;}
    break;

  case 65:
#line 607 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changeadd()[AttrValRecord_Counter++] 
       = temporal_AttrValRecord;
    ;}
    break;

  case 66:
#line 613 "ldif.y"
    {
        AttrValRecord_Counter = 0;
        temporal_data.datalist()[data_counter - 1].data().change()
          .changetype().changeadd()[AttrValRecord_Counter++] 
        = temporal_AttrValRecord;
    ;}
    break;

  case 67:
#line 623 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changedelete().set_size(0);
    ;}
    break;

  case 69:
#line 635 "ldif.y"
    {
       if(!error_recovery)
       {
         TTCN_warning("line number %d contains more than one data", line_number);
         error_recovery = true;
       }
       erroneous = true;
    ;}
    break;

  case 70:
#line 645 "ldif.y"
    {
       if(!error_recovery)
       {
          TTCN_warning("line number %d contains more than one data", line_number);
          error_recovery = true;
       }
       erroneous = true;
    ;}
    break;

  case 71:
#line 655 "ldif.y"
    {
      if(!error_recovery)
      {
         TTCN_warning("deleteoldrdn missing from the change moddn structure"
         " ending on the %dth line",line_number-1);
         error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = false;
      erroneous = true;
    ;}
    break;

  case 72:
#line 668 "ldif.y"
    {
      if(!error_recovery)
      {
         TTCN_warning("line number %d contains more than one data", line_number);
         error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = false;
      erroneous = true;
    ;}
    break;

  case 73:
#line 682 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().modtype() = CHARSTRING("MODRDN");
    ;}
    break;

  case 74:
#line 687 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().modtype() = CHARSTRING("MODDN");
    ;}
    break;

  case 75:
#line 692 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong moddn type at line %d",
          line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().modtype() = CHARSTRING("ERROR");
      erroneous = true;
    ;}
    break;

  case 76:
#line 707 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() 
        = *((yyvsp[(1) - (2)].string_val));
      delete (yyvsp[(1) - (2)].string_val);
    ;}
    break;

  case 77:
#line 714 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() 
        = *((yyvsp[(2) - (3)].string_val));
      delete (yyvsp[(2) - (3)].string_val);
    ;}
    break;

  case 78:
#line 721 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("The keyword newrdn was expected at line "
          "%d",line_number);
        error_recovery = true;
      }
      erroneous = true;
    ;}
    break;

  case 79:
#line 731 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("The keyword newrdn was expected at line "
          "%d",line_number);
        error_recovery = true;
      }
      erroneous = true;
    ;}
    break;

  case 80:
#line 741 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong newrdn value at line %d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() = "ERROR";
      erroneous = true;
    ;}
    break;

  case 81:
#line 752 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong newrdn value at line %d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() = "ERROR";
      erroneous = true;
    ;}
    break;

  case 82:
#line 766 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = false;
    ;}
    break;

  case 83:
#line 771 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = true;
    ;}
    break;

  case 84:
#line 776 "ldif.y"
    {
       if(!error_recovery)
       {
          TTCN_warning("Wrong deleteoldrdn value at line %d",line_number);
          error_recovery = true;
       }
       temporal_data.datalist()[data_counter - 1].data().change()
          .changetype().changemoddn().deleteoldrdn() = false;
       erroneous = true;
    ;}
    break;

  case 85:
#line 790 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = *((yyvsp[(2) - (3)].string_val));
      delete (yyvsp[(2) - (3)].string_val);
    ;}
    break;

  case 86:
#line 797 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = *((yyvsp[(2) - (3)].string_val));
      delete (yyvsp[(2) - (3)].string_val);
    ;}
    break;

  case 87:
#line 804 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().base64__distinguished() 
        = *((yyvsp[(3) - (4)].string_val));
      delete (yyvsp[(3) - (4)].string_val);
    ;}
    break;

  case 88:
#line 811 "ldif.y"
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior() 
        = OPTIONAL<LDIF::NewSuperior>(OMIT_VALUE);
    ;}
    break;

  case 89:
#line 817 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong newsuperior value at line %d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = "ERROR";
      erroneous = true;
    ;}
    break;

  case 90:
#line 829 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong newsuperior value at line %d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = "ERROR";
      erroneous = true;
    ;}
    break;

  case 91:
#line 841 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("The keyword newsuperior was expected at line "
          "%d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = "ERROR";
      erroneous = true;      
    ;}
    break;

  case 92:
#line 854 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("The keyword newsuperior was expected at line "
          "%d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = "ERROR";
      erroneous = true;      
    ;}
    break;

  case 94:
#line 871 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify().set_size(0)
    ;}
    break;

  case 95:
#line 876 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("line number %d contains more than one data", line_number);
        error_recovery = true;
      }
    ;}
    break;

  case 96:
#line 887 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
    ;}
    break;

  case 97:
#line 893 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
    ;}
    break;

  case 98:
#line 899 "ldif.y"
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
    ;}
    break;

  case 99:
#line 905 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("line number %d contains more than one data", line_number);
        error_recovery = true;
      }
      erroneous = true;
    ;}
    break;

  case 100:
#line 914 "ldif.y"
    {
       if(!error_recovery)
       {
         TTCN_warning("Hyphen expected at line %d",line_number);
         error_recovery = true;
       }
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
         erroneous = true;
    ;}
    break;

  case 101:
#line 929 "ldif.y"
    {
      temporal_AttrValRecord.attributevalue() =OPTIONAL<LDIF::ValueUnion>(OMIT_VALUE);
      temporal_AttrValRecord.optionlist().set_size(0);
      temporal_changemodifydata.attrvalrecordlist()[0] = temporal_AttrValRecord;
      AttrValRecord_Counter = 1;
    ;}
    break;

  case 102:
#line 936 "ldif.y"
    {
      if(!error_recovery){
        TTCN_warning("Attribute error at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.attributetype() = CHARSTRING("ERROR");
      temporal_AttrValRecord.optionlist().set_size(0);
      temporal_AttrValRecord.attributevalue()=OPTIONAL<LDIF::ValueUnion>(OMIT_VALUE);
      temporal_changemodifydata.attrvalrecordlist()[0] = temporal_AttrValRecord;
      erroneous = true;
      yyerrok;
    ;}
    break;

  case 103:
#line 952 "ldif.y"
    {
       temporal_changemodifydata.operation() = CHARSTRING("add");
       temporal_changemodifydata.attrvalrecordlist().set_size(0);
    ;}
    break;

  case 104:
#line 957 "ldif.y"
    {
       temporal_changemodifydata.operation() = CHARSTRING("delete");
       temporal_changemodifydata.attrvalrecordlist().set_size(0);
    ;}
    break;

  case 105:
#line 962 "ldif.y"
    {
       temporal_changemodifydata.operation() = CHARSTRING("replace");
       temporal_changemodifydata.attrvalrecordlist().set_size(0);
    ;}
    break;

  case 106:
#line 967 "ldif.y"
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong modification operation name at line "
          "%d",line_number);
        error_recovery = true;
      }
      temporal_changemodifydata.operation() = CHARSTRING("ERROR");
      temporal_changemodifydata.attrvalrecordlist().set_size(0);
      erroneous = true;
      yyerrok;
    ;}
    break;

  case 107:
#line 983 "ldif.y"
    {
      temporal_changemodifydata.attrvalrecordlist()
        [AttrValRecord_Counter++] = temporal_AttrValRecord;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2676 "ldif.tab.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 990 "ldif.y"


void yyerror(const char */*s*/)
{
}

UNIVERSAL_CHARSTRING LDIF::f__utf82unichar(const OCTETSTRING& pl__utf8)
{
  UNIVERSAL_CHARSTRING ret;
  ret.decode_utf8(pl__utf8.lengthof(), (const unsigned char *)pl__utf8);
  return ret;
}

extern FILE *yyin;
LDIF::LDIFData LDIF::f__ImportLDIF(const CHARSTRING& pl_file_name, const BOOLEAN& pl_resolve_env)
{
  temporal_data.version() = -1;
  temporal_data.datalist().set_size(0);

  yyin = fopen(pl_file_name,"r");

  if(yyin != NULL)
  {
     line_number = 0;
     AttrValRecord_Counter = 0;
     option_counter = 0;
     data_counter = 0;
     control_counter = 0;
     modification_counter = 0;
     erroneous = false;
     inner_resolve_env = pl_resolve_env;

     yyrestart(yyin);
     if(yyparse() != 0)
     {
       temporal_data.version() = -1;
     }else if(erroneous)
     {
       temporal_data.version() = -1;
     }else{
       bool selection = temporal_data.datalist()[0].data().ischosen( LDIFChoice::ALT_content);
       for(int i = 1; i < temporal_data.datalist().size_of(); i++)
       {
         if(selection != temporal_data.datalist()[i].data().ischosen( LDIFChoice::ALT_content) )
         {
           erroneous = true;
           TTCN_warning("Content and change records "
             "can not be mixed in one file");
         }
       }
       
       for(int i = 0; i < temporal_data.datalist().size_of(); i++)
       {
          if(temporal_data.datalist()[i].data().ischosen( LDIFChoice::ALT_change)
            && temporal_data.datalist()[i].data().change().changetype()
                 .ischosen(ChangeType::ALT_changemodify ) )
          {
             for(int j = 0;
                 j < temporal_data.datalist()[i].data().change()
                       .changetype().changemodify().size_of();
                 j++)
             {
               CHARSTRING type = temporal_data.datalist()[i].data()
                                   .change().changetype().changemodify()[j]
                                   .attrvalrecordlist()[0].attributetype();
               for(int k = 1;
                   k < temporal_data.datalist()[i].data()
                         .change().changetype().changemodify()[j]
                         .attrvalrecordlist().size_of(); 
                  k++)
               {
                 if(type != temporal_data.datalist()[i].data().change()
                             .changetype().changemodify()[j]
                             .attrvalrecordlist()[k].attributetype())
                 {
                   TTCN_warning("The %dth modified attribute's type is "
                     "different from the one described in the %dth "
                     "changerecord's %dth modify record (%s) (%s)",k,i,j,
                     (const char*)type,(const char*)temporal_data.datalist()[i]
                     .data().change().changetype().changemodify()[j]
                     .attrvalrecordlist()[k].attributetype());
                   erroneous = true;
                 }
               }
             }
          }
       }
       if(erroneous)
         temporal_data.version() = -1;
     }
  }else{
     TTCN_warning("The file %s could not be opened",(const char*)pl_file_name);
  }

  fclose(yyin);
  return temporal_data;	
} 

bool is_base64(const char *pl_string)
  {
    bool is_safestring=false;
    int i=0;
    char c=pl_string[i];    
    while(c && !is_safestring)
    {
      if((c>64 && c<91) || (c>96 && c<123) || (c>47 && c<58))
      {
        c=pl_string[++i];
        continue;
      }
      is_safestring = (c==44) || ((c>=1) && (c<=46) && (c!=43)) || ((c>=58) && (c<=64)
      && (c!=61)) || ((c>=91) && (c<=96)) || ((c>=123) && (c<=127));
      c=pl_string[++i];
    }
    return !is_safestring;
  }
  
void fprintf_AVRL(FILE *pl_f, const LDIF::AttrValRecordList& pl_varl,const int pl_start)
{
  for(int j=pl_start;j<pl_varl.lengthof();j++)
  {
    //attributetype
    fprintf(pl_f,"%s",(const char*)pl_varl[j].attributetype());
    //optionlist
    for(int k=0;k<pl_varl[j].optionlist().lengthof();k++)
    {
      fprintf(pl_f,";%s",(const char*)pl_varl[j].optionlist()[k]);	      
    }
    //attributevalue
    if(!pl_varl[j].attributevalue().ispresent())continue;
    switch(((LDIF::ValueUnion)pl_varl[j].attributevalue()).get_selection())
    {		     
    case(LDIF::ValueUnion::ALT_safe__string):
  	     fprintf(pl_f,": %s\n",(const char*)((LDIF::ValueUnion)pl_varl[j].attributevalue()).safe__string());
  	     break;

    case(LDIF::ValueUnion::ALT_base64__string):
  	     fprintf(pl_f,":: %s\n",(const char*)((LDIF::ValueUnion)pl_varl[j].attributevalue()).base64__string());
  	     break;
  	     
    case(LDIF::ValueUnion::ALT_url):
  	     fprintf(pl_f,":<%s\n",(const char*)((LDIF::ValueUnion)pl_varl[j].attributevalue()).url());
  	     break;
  	     
    case(LDIF::ValueUnion::UNBOUND_VALUE):
  	     break;
    }	     
  }
} 

BOOLEAN LDIF::f__ExportLDIF(const CHARSTRING& pl_file_name, const LDIF::LDIFData& pl_LDIF_data)
{  
  FILE *ldif_out;
  ldif_out = fopen(pl_file_name,"wt");
  if(ldif_out==NULL)
  {
    TTCN_warning("The file %s could not be opened",(const char*)pl_file_name);
    return false;
  }
  try
  {
    //version
    fprintf(ldif_out,"version: %d",pl_LDIF_data.version().ispresent()?(int)(INTEGER)pl_LDIF_data.version():1);
    //dn
    for(int i=0;i<pl_LDIF_data.datalist().lengthof();i++)
    {    
      fprintf(ldif_out,"\n%s",is_base64((const char*)pl_LDIF_data.datalist()[i].dn__string())?"dn::":"dn:");
      fprintf(ldif_out," %s\n",(const char*)pl_LDIF_data.datalist()[i].dn__string());
      //LDIFChoice
      if(pl_LDIF_data.datalist()[i].data().get_selection()==1) //CONTENT
      {
	fprintf_AVRL(ldif_out,pl_LDIF_data.datalist()[i].data().content(),0);
      }
      else
      {
	if(pl_LDIF_data.datalist()[i].data().get_selection()==2)//CHANGE
	{
          //controllist
          for(int j=0;j<pl_LDIF_data.datalist()[i].data().change().controllist().lengthof();j++)
          {
	    fprintf(ldif_out,"control: %s",(const char*)pl_LDIF_data.datalist()[i].data().change().controllist()[j].ldapoid());
	    if(pl_LDIF_data.datalist()[i].data().change().controllist()[j].criticality().ispresent())
	    {
	      fprintf(ldif_out," %s",(bool)((BOOLEAN)pl_LDIF_data.datalist()[i].data().change().controllist()[j].criticality())?"true":"false");
	    }
	    if(pl_LDIF_data.datalist()[i].data().change().controllist()[j].controlvalue().ispresent())
	    {
	      fprintf(ldif_out,": %s",(const unsigned char*)((OCTETSTRING)pl_LDIF_data.datalist()[i].data().change().controllist()[j].controlvalue()));
	    }
	    fprintf(ldif_out,"\n");
	  }
	  //changetype
	  switch(pl_LDIF_data.datalist()[i].data().change().changetype().get_selection())
	  {
	  case(LDIF::ChangeType::ALT_changeadd):
	           fprintf(ldif_out,"changetype: add\n");
		   fprintf_AVRL(ldif_out,pl_LDIF_data.datalist()[i].data().change().changetype().changeadd(),0);
		   break;

	  case(LDIF::ChangeType::ALT_changedelete):
	           fprintf(ldif_out,"changetype: delete\n");
	           /*for(int j=0;j<pl_LDIF_data.datalist()[i].data().change().changetype().changedelete().lengthof();j++)
                   {
		     
		   }*/
		   break;

	  case(LDIF::ChangeType::ALT_changemodify):
	           fprintf(ldif_out,"changetype: modify\n");
	           for(int j=0;j<pl_LDIF_data.datalist()[i].data().change().changetype().changemodify().lengthof();j++)
                   {
		     fprintf(ldif_out,"%s: ",(const char*)pl_LDIF_data.datalist()[i].data().change().changetype().changemodify()[j].operation());
		     fprintf(ldif_out,"%s\n",(const char*)pl_LDIF_data.datalist()[i].data().change().changetype().changemodify()[j].attrvalrecordlist()[0].attributetype());
                     fprintf_AVRL(ldif_out,pl_LDIF_data.datalist()[i].data().change().changetype().changemodify()[j].attrvalrecordlist(),1);
		     fprintf(ldif_out,"-\n");
		   }
		   break;

	  case(LDIF::ChangeType::ALT_changemoddn):
	           fprintf(ldif_out,"changetype: ");
                   fprintf(ldif_out,"%s\n",((const char*)pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().modtype())[3]=='R'?"modrdn":"moddn");
		   fprintf(ldif_out,"newrdn: %s\n",(const char*)pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().newrdn());
		   fprintf(ldif_out,"deleteoldrdn: %d\n",(bool)pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().deleteoldrdn()?1:0);
		   if(pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().newsuperior().ispresent())
		   {			
                     switch(((NewSuperior)pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().newsuperior()).get_selection())
		     {
		       case(LDIF::NewSuperior::ALT_distinguished):
		        	fprintf(ldif_out,"newsuperior: %s\n",(const char*)((NewSuperior)pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().newsuperior()).distinguished());
				break;
	               case(LDIF::NewSuperior::ALT_base64__distinguished):
		        	fprintf(ldif_out,"newsuperior: %s\n",(const char*)((NewSuperior)pl_LDIF_data.datalist()[i].data().change().changetype().changemoddn().newsuperior()).base64__distinguished());
				break;
        default:
          break;
		     }
		   }
		   break;

	  case(LDIF::ChangeType::UNBOUND_VALUE):
	           break;
	  }

	}//end of CHANGE
      }    
    }//end of datalist
  }catch(...)
    {
      TTCN_warning("ERROR in exporting to %s.",(const char*)pl_file_name);
      fflush(ldif_out);
      fclose(ldif_out);
      return false;
    }
  fflush(ldif_out);
  fclose(ldif_out); 
  return true;
}


