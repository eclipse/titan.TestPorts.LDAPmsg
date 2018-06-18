%option noyywrap
%{
/******************************************************************************
* Copyright (c) 2004, 2015  Ericsson AB
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the Eclipse Public License v1.0
* which accompanies this distribution, and is available at
* http://www.eclipse.org/legal/epl-v10.html
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
//  File:               ldif.lex
//  Description:        LDIF tokenizer source code
//  Rev:                R2A01
//  Prodnr:             CNL 113 385
// 
#include <stdio.h>
#include <string.h>
#include "LDIF.hh"
#include "ldif.tab.hh"


extern int line_number;
boolean change_type = false;
boolean modify_type = false;
boolean moddn_type = false;
boolean moddn_keyword = false;

#define YY_INPUT(buf,result,max_size) \
{ \
  int c0 = getc(yyin); \
  int c1 = 0;\
  int n = 0;\
  if( c0 == EOF){ \
    result = YY_NULL; \
  }else{\
    while( n < max_size - 1){\
      c1 = getc(yyin);\
      if(c0 != '\n' || c1 != ' '){\
        if(c0 == EOF){\
          result = n-1;\
          break;\
        }\
        buf[n] = c0; \
        c0 = c1;\
        ++n;\
      }else{\
        c0 = getc(yyin);\
        line_number++;\
      }\
    }\
    if(c1 != EOF){\
      buf[n] = c1;\
      result = ++n;\
    }else{\
      result = n;\
    }\
  }\
}

%}
SAFE_CHAR [\x01-\x09\x0B-\x0C\x0E-\x7F]
SAFE_INIT_CHAR [\x01-\x09\x0B-\x0C\x0E-\x1F\x21-\x39\x3B\x3D-\x7F]
BASE64_CHAR [\x2B\x2F\x30-\x39\x3D\x41-\x5A\x61-\x7A]
CR \x0D
LF \x0A
UTF8_CHAR SAFE_CHAR
SPECIALS [\,\=\+\<\>\#\;]
DIGIT [0-9]
CHAR [a-zA-Z]
KEYCHAR [a-zA-Z0-9\-]
HEXCHAR [0-9ABCDEFabcdef]
HEXPAIR {HEXCHAR}{HEXCHAR}
%x distinguished
%x zero_one
%x safe_possible
%x base64_possible
%x url_possible
%x quoted_distinguished
%%
^\n          {line_number++;}
<*>{CR}{LF}  {
                line_number++;
                BEGIN(INITIAL);
                if(moddn_type) moddn_keyword = true;
                return(SEP);
             }
<*>{LF}      {
                line_number++;
                BEGIN(INITIAL);
                if(moddn_type) moddn_keyword = true; 
                return(SEP);
             }
\;           {return(SEMICOLON);}
\-           {
                modify_type = true;
                return(HYPHEN);}
\<           {return(GREATER);}
<*>[ ]+      {}


<zero_one>0  {
               return(ZERO);
               BEGIN(INITIAL);
             }
<zero_one>1  {
               return(ONE);
               BEGIN(INITIAL);
             }

\#[^\n]*\n      {line_number++;}
version:        {return(VERSION);}
^(dn:)          {
                   BEGIN(safe_possible);
                   modify_type = false;
                   moddn_type = false;
                   return(DN);
                }
<INITIAL>:      {
                   BEGIN(safe_possible);
                   return(COLON);
                }
<safe_possible>:    {
                       BEGIN(base64_possible);
                       return(COLON);
                    }
<safe_possible>\<   {
                       BEGIN(url_possible);
                       return(GREATER);
                    }
control:            {return(BISON_CONTROL);}
true         {return(BISON_TRUE);}
false        {return(BISON_FALSE);}
changetype:     {
                   change_type = true;
                   modify_type = false;
                   return(CHANGETYPE);
                }
add             {
                   if(change_type)
                   {
                      change_type = false;
                      return(ADD);
                   }else{
                      yylval.string_val = new CHARSTRING(yytext);
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
add:            {
                   if(modify_type)
                   {
                      modify_type = false;
                      return(ADD_COLON);
                   }else{
                      yylval.string_val = new CHARSTRING("add");
                      unput(':');
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
delete          {
                   if(change_type)
                   {
                      change_type = false;
                      return(DELETE);
                   }else{
                      yylval.string_val = new CHARSTRING(yytext);
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
delete:         {
                   if(modify_type)
                   {
                      modify_type = false;
                      return(DELETE_COLON);
                   }else{
                      yylval.string_val = new CHARSTRING("delete");
                      unput(':');
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
replace:        {
                   if(modify_type)
                   {
                      modify_type = false;
                      return(REPLACE);
                   }else{
                      yylval.string_val = new CHARSTRING("replace");
                      unput(':');
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                } 
modrdn          {
                   if(change_type)
                   {
                      change_type = false;
                      moddn_type = true; 
                      return(MODRDN);
                   }else{
                      yylval.string_val = new CHARSTRING(yytext);
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
moddn           {
                   if(change_type)
                   {
                      change_type = false;
                      moddn_type = true;
                      return(MODDN);
                   }else{
                      yylval.string_val = new CHARSTRING(yytext);
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
newrdn:         {
                   if(moddn_keyword)
                   {
                      BEGIN(safe_possible);
                      moddn_keyword = false;
                      return(NEWRDN);
                   }else{
                      yylval.string_val = new CHARSTRING("newrdn");
                      unput(':');
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
deleteoldrdn:   {
                   if(moddn_keyword)
                   {
                      BEGIN(zero_one);
                      moddn_keyword = false;
                      return(DELETEOLDRDN);
                   }else{
                      yylval.string_val = new CHARSTRING("deleteoldrdn");
                      unput(':');
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
newsuperior:    {
                   if(moddn_keyword)
                   {
                      BEGIN(safe_possible);
                      moddn_keyword = false;
                      return(NEWSUPERIOR);
                   }else{
                      yylval.string_val = new CHARSTRING("newsuperior");
                      unput(':');
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
modify          {
                   if(change_type)
                   {
                      change_type = false;
                      modify_type = true;
                      return(MODIFY);
                   }else{
                      yylval.string_val = new CHARSTRING(yytext);
                      return(CHAR_ATTRIBUTE_TYPE);
                   }
                }
{DIGIT}+        {
                   yylval.string_val = new CHARSTRING(yytext);
                   return(INTEGER_VAL);
                }
{DIGIT}+("."{DIGIT}+){0,1}      {
                                  yylval.string_val = new CHARSTRING(yytext);
                                  return(FLOAT_VAL);
                                }
{DIGIT}+("."{DIGIT}+)*          {
                                  yylval.string_val = new CHARSTRING(yytext);
                                  return(LDAP_OID);
                                }
<INITIAL>{CHAR}{KEYCHAR}*       {
                                  yylval.string_val = new CHARSTRING(yytext);
                                  return(CHAR_ATTRIBUTE_TYPE);
                                }
<url_possible>[^\n]*            {
                                  yylval.string_val = new CHARSTRING(yytext);
                                  line_number++;return(URL_STRING);
                                }
<base64_possible>{BASE64_CHAR}+ {
                                  yylval.string_val = new CHARSTRING(yytext);
                                  return(SAFE_BASE64_STRING);
                                }
<safe_possible>{SAFE_INIT_CHAR}{SAFE_CHAR}*  {
                                  yylval.string_val = new CHARSTRING(yytext);
                                  return(SAFE_STRING);
                                 }
.  {TTCN_warning(" error: %s ",yytext);}
%%
