/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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

/******************************************************************************
* Copyright (c) 2000-2018 Ericsson Telecom AB
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
//  Rev:                R9A
//  Prodnr:             CNL 113 385
//


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 45 "ldif.y"
{
	CHARSTRING *string_val;
}
/* Line 1489 of yacc.c.  */
#line 119 "ldif.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

