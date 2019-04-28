%{
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

%}
%union {
	CHARSTRING *string_val;
}
%start ldif_file
%token VERSION SEP
%token DN COLON SAFE_STRING SAFE_BASE64_STRING
%token GREATER SEMICOLON HYPHEN
%token FLOAT_VAL INTEGER_VAL BISON_CONTROL
%token BISON_TRUE BISON_FALSE CHANGETYPE
%token ADD DELETE MODRDN MODDN NEWRDN DELETEOLDRDN
%token ADD_COLON DELETE_COLON
%token NEWSUPERIOR MODIFY REPLACE
%token URL_STRING ZERO ONE LDAP_OID
%token CHAR_ATTRIBUTE_TYPE
%%

ldif_file:
  version_spec ldif_end
| ldif_end
  {
    temporal_data.version() = OPTIONAL<INTEGER>(OMIT_VALUE);
  }
;

ldif_end:
  ldif_attrval_record optional_separators ldif_end
| ldif_attrval_record ldif_end
| ldif_attrval_record
| ldif_change_record optional_separators ldif_end
| ldif_change_record ldif_end
| ldif_change_record
;
    
optional_separators:
  SEP optional_separators
| SEP
;

ldif_attrval_record : 
  dn_spec SEP attrval_specs
;

attrval_specs :
  attrval_specs attrval_spec
    { 
      temporal_data.datalist()[data_counter-1].data().content()
        [AttrValRecord_Counter++] = temporal_AttrValRecord;
    }
| attrval_spec
    {
      temporal_data.datalist()[data_counter-1].data().content()
        [AttrValRecord_Counter++] = temporal_AttrValRecord;
    }
;

ldif_change_record :
  dn_spec SEP controls changerecord
;

controls : 
  controls control 
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .controllist()[control_counter++] = temporal_Control;
    }
| 
    {
       temporal_data.datalist()[data_counter-1].data().change()
         .controllist().set_size(0);
    }
;

version_spec :
  VERSION version_number optional_separators
    {
       *($<string_val>2) == CHARSTRING("1") ? temporal_data.version() = 1 
         : temporal_data.version() = OPTIONAL<INTEGER>(OMIT_VALUE);
       delete $<string_val>2;
    }
| VERSION error optional_separators 
    {
       TTCN_warning("Version error at line %d",line_number);
       error_recovery = false;
       erroneous = true;
    }
| VERSION version_number error SEP
    {
       TTCN_warning("Version error at line %d",line_number);
       erroneous = true;
       delete $<string_val>2;
    }
| error SEP
    {
       TTCN_warning("Version error at line %d",line_number);
       error_recovery = false;
       erroneous = true;
    }
;
    
version_number : 
  FLOAT_VAL
    {
       $<string_val>$ = $<string_val>1;
    }
| INTEGER_VAL
    {
       $<string_val>$ = $<string_val>1;
    }
;

dn_spec : 
  DN SAFE_STRING
    {
       AttrValRecord_Counter = 0;
       modification_counter = 0;
       control_counter = 0;
       option_counter = 0;



       if(!inner_resolve_env)
       {
         temporal_data.datalist()[data_counter++].dn__string()
           = *($<string_val>2);
       }else{
         CHARSTRING temp_char = CHARSTRING(*($<string_val>2));
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



       delete $<string_val>2;
    } 
| DN COLON SAFE_BASE64_STRING
    {
       AttrValRecord_Counter = 0;
       modification_counter = 0;
       control_counter = 0;
       option_counter = 0;
       temporal_data.datalist()[data_counter++].dn__string() 
         = *($<string_val>3);
       delete $<string_val>3;
    }
| DN error 
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
    }
| DN COLON error 
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
    }
;

control : 
  BISON_CONTROL ldap_oid control_mid control_end SEP 
    {
       temporal_Control.ldapoid() = *($<string_val>2);
       delete $<string_val>2;
    }
| BISON_CONTROL error control_mid control_end SEP 
    {
       if(!error_recovery)
       {
         TTCN_warning("ldap_oid error at line %d",line_number);
         error_recovery = true;
       }
       temporal_Control.ldapoid() = "0";
       erroneous = true;
    }
| BISON_CONTROL ldap_oid control_mid control_end error 
    {
       if(!error_recovery)
       {
         TTCN_warning("line number %d contains more than one data", line_number);
         error_recovery = true;
       }
       temporal_Control.ldapoid() = "0";
       erroneous = true;
    }
;

control_mid : 
  BISON_TRUE
    {
       temporal_Control.criticality() = true;
    }
| BISON_FALSE
    {
       temporal_Control.criticality() = false;
    }
| 
    {
       temporal_Control.criticality() = OPTIONAL<BOOLEAN>(OMIT_VALUE);
    }
;

control_end :
  COLON value_spec 
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
    }
| 
    {
       temporal_Control.controlvalue() = OPTIONAL<OCTETSTRING>(OMIT_VALUE);
    }
;

ldap_oid :
  FLOAT_VAL
    {
       $<string_val>$ = $<string_val>1;
    }
| INTEGER_VAL
    {
       $<string_val>$ = $<string_val>1;
    }
| LDAP_OID
    {
       $<string_val>$ = $<string_val>1;
    }
;

attrval_spec : 
  AttributeDescription COLON value_spec SEP
| AttributeDescription COLON SEP      
    {
      temporal_AttrValRecord.attributevalue()().safe__string()
        = "";
    }
| error COLON value_spec SEP
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
    }
| error COLON SEP
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
    }
| AttributeDescription error value_spec SEP
    {
       TTCN_warning("Attribute must be separated from value with colon at line %d",line_number);
       error_recovery = false;
       erroneous = true;
    }
| AttributeDescription COLON error SEP
    {
       TTCN_warning("Value error at line %d",line_number);
       error_recovery = false;
       temporal_AttrValRecord.attributevalue()().safe__string() 
         = CHARSTRING("ERROR");
       erroneous = true;
    }
;

value_spec :
  SAFE_STRING
    {


       if(!inner_resolve_env)
       {
         temporal_AttrValRecord.attributevalue()().safe__string()
           = CHARSTRING(*($<string_val>1));
       }else{
         CHARSTRING temp_char = CHARSTRING(*($<string_val>1));
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




       delete $<string_val>1;
    }
| COLON SAFE_BASE64_STRING
    {
       temporal_AttrValRecord.attributevalue()().base64__string() 
         = *($<string_val>2);
       delete $<string_val>2;
    }
| GREATER URL_STRING
    {
       temporal_AttrValRecord.attributevalue()().url() = *($<string_val>2);
       delete $<string_val>2;
    }
;

AttributeDescription : 
  AttributeType options
    {
      temporal_AttrValRecord.attributetype() = *($<string_val>1);
      delete $<string_val>1;
    }
| AttributeType
    {
      temporal_AttrValRecord.attributetype() = *($<string_val>1);
      delete $<string_val>1;
    }
| error options
    {
      if(!error_recovery)
      {
        TTCN_warning("Attribute error at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.attributetype() = CHARSTRING("ERROR");
      erroneous = true;
    }
;

AttributeType :
  ldap_oid
    {
      $<string_val>$ = $<string_val>1;
      option_counter = 0;
      temporal_AttrValRecord.optionlist().set_size(0);
    }
| CHAR_ATTRIBUTE_TYPE
    {
      $<string_val>$ = $<string_val>1;
      option_counter = 0;
      temporal_AttrValRecord.optionlist().set_size(0);
    }
;

options : 
  SEMICOLON CHAR_ATTRIBUTE_TYPE
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *($<string_val>2);
      delete $<string_val>2;
    }
| SEMICOLON INTEGER_VAL
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *($<string_val>2);
      delete $<string_val>2;
    }
| options SEMICOLON INTEGER_VAL
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *($<string_val>3);
      delete $<string_val>3;
    }
| options SEMICOLON CHAR_ATTRIBUTE_TYPE
    {
      temporal_AttrValRecord.optionlist()[option_counter++] = *($<string_val>3);
      delete $<string_val>3;
    }
| SEMICOLON error
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong option syntax at line %d",line_number);
        error_recovery = true;
      }
      temporal_AttrValRecord.optionlist()[option_counter++] = "ERROR";
      erroneous = true;
    }
;
    
changerecord : 
  CHANGETYPE changerecord_end 
    {
      if(error_recovery)
        error_recovery = false;
    }
;

changerecord_end : 
  change_add
| change_delete
| change_modify	
| change_moddn
;

change_add : 
  ADD SEP change_add_end
| ADD SEP error 
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
    }
;

change_add_end : 
  change_add_end attrval_spec
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changeadd()[AttrValRecord_Counter++] 
       = temporal_AttrValRecord;
    }
| attrval_spec
    {
        AttrValRecord_Counter = 0;
        temporal_data.datalist()[data_counter - 1].data().change()
          .changetype().changeadd()[AttrValRecord_Counter++] 
        = temporal_AttrValRecord;
    }
;

change_delete : 
  DELETE SEP
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changedelete().set_size(0);
    }
;

change_moddn :
  change_moddn_start SEP change_moddn_middle
  SEP DELETEOLDRDN zero_or_one SEP change_moddn_end
  
| change_moddn_start error change_moddn_middle
  SEP DELETEOLDRDN zero_or_one SEP change_moddn_end
    {
       if(!error_recovery)
       {
         TTCN_warning("line number %d contains more than one data", line_number);
         error_recovery = true;
       }
       erroneous = true;
    }
| change_moddn_start SEP change_moddn_middle
  error DELETEOLDRDN zero_or_one SEP change_moddn_end
    {
       if(!error_recovery)
       {
          TTCN_warning("line number %d contains more than one data", line_number);
          error_recovery = true;
       }
       erroneous = true;
    }
|  change_moddn_start SEP change_moddn_middle
   SEP error zero_or_one SEP change_moddn_end
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
    }  
|  change_moddn_start SEP change_moddn_middle
   SEP DELETEOLDRDN zero_or_one error change_moddn_end
    {
      if(!error_recovery)
      {
         TTCN_warning("line number %d contains more than one data", line_number);
         error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = false;
      erroneous = true;
    }  
;

change_moddn_start : 
  MODRDN
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().modtype() = CHARSTRING("MODRDN");
    }
| MODDN
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().modtype() = CHARSTRING("MODDN");
    }
| error 
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
    }
;

change_moddn_middle :
  NEWRDN SAFE_STRING
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() 
        = *($<string_val>1);
      delete $<string_val>1;
    }
| NEWRDN COLON SAFE_BASE64_STRING
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() 
        = *($<string_val>2);
      delete $<string_val>2;
    }
| error SAFE_STRING
    {
      if(!error_recovery)
      {
        TTCN_warning("The keyword newrdn was expected at line "
          "%d",line_number);
        error_recovery = true;
      }
      erroneous = true;
    }
| error COLON SAFE_STRING
    {
      if(!error_recovery)
      {
        TTCN_warning("The keyword newrdn was expected at line "
          "%d",line_number);
        error_recovery = true;
      }
      erroneous = true;
    }
| NEWRDN error
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong newrdn value at line %d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() = "ERROR";
      erroneous = true;
    }
| NEWRDN COLON error
    {
      if(!error_recovery)
      {
        TTCN_warning("Wrong newrdn value at line %d",line_number);
        error_recovery = true;
      }
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newrdn() = "ERROR";
      erroneous = true;
    }
;

zero_or_one : 
  ZERO
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = false;
    }
| ONE 
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemoddn().deleteoldrdn() = true;
    }
| error 
    {
       if(!error_recovery)
       {
          TTCN_warning("Wrong deleteoldrdn value at line %d",line_number);
          error_recovery = true;
       }
       temporal_data.datalist()[data_counter - 1].data().change()
          .changetype().changemoddn().deleteoldrdn() = false;
       erroneous = true;
    }
;

change_moddn_end : 
  NEWSUPERIOR SAFE_STRING SEP
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = *($<string_val>2);
      delete $<string_val>2;
    }
| NEWSUPERIOR CHAR_ATTRIBUTE_TYPE SEP
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().distinguished() 
        = *($<string_val>2);
      delete $<string_val>2;
    }
|  NEWSUPERIOR COLON SAFE_BASE64_STRING SEP
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior()().base64__distinguished() 
        = *($<string_val>3);
      delete $<string_val>3;
    }
| 
    {
      temporal_data.datalist()[data_counter - 1].data().change()
        .changetype().changemoddn().newsuperior() 
        = OPTIONAL<LDIF::NewSuperior>(OMIT_VALUE);
    }
| NEWSUPERIOR error SEP
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
    }
| NEWSUPERIOR COLON error SEP
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
    }
| error SAFE_STRING SEP
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
    }
| error COLON SAFE_BASE64_STRING SEP
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
    }
;
		
change_modify : 
  MODIFY SEP mod_spec
| MODIFY SEP 
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify().set_size(0)
    }
| MODIFY error mod_spec
    {
      if(!error_recovery)
      {
        TTCN_warning("line number %d contains more than one data", line_number);
        error_recovery = true;
      }
    }
;

mod_spec : 
  mod_spec mod_spec_start mod_spec_middle SEP optional_attrval_spec HYPHEN SEP 
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
    }
| mod_spec_start mod_spec_middle SEP optional_attrval_spec HYPHEN SEP 
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
    }
| error SEP optional_attrval_spec HYPHEN SEP 
    {
       temporal_data.datalist()[data_counter - 1].data().change()
         .changetype().changemodify()[modification_counter++] 
         = temporal_changemodifydata;
    }
| mod_spec_start mod_spec_middle error optional_attrval_spec HYPHEN SEP 
    {
      if(!error_recovery)
      {
        TTCN_warning("line number %d contains more than one data", line_number);
        error_recovery = true;
      }
      erroneous = true;
    }
| mod_spec_start mod_spec_middle SEP optional_attrval_spec error SEP 
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
    }
;

mod_spec_middle : 
  AttributeDescription
    {
      temporal_AttrValRecord.attributevalue() =OPTIONAL<LDIF::ValueUnion>(OMIT_VALUE);
      temporal_AttrValRecord.optionlist().set_size(0);
      temporal_changemodifydata.attrvalrecordlist()[0] = temporal_AttrValRecord;
      AttrValRecord_Counter = 1;
    }
| error
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
    }
;

mod_spec_start : 
  ADD_COLON
    {
       temporal_changemodifydata.operation() = CHARSTRING("add");
       temporal_changemodifydata.attrvalrecordlist().set_size(0);
    }
| DELETE_COLON
    {
       temporal_changemodifydata.operation() = CHARSTRING("delete");
       temporal_changemodifydata.attrvalrecordlist().set_size(0);
    }
| REPLACE
    {
       temporal_changemodifydata.operation() = CHARSTRING("replace");
       temporal_changemodifydata.attrvalrecordlist().set_size(0);
    }
| error COLON
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
    }
;

optional_attrval_spec : 
  optional_attrval_spec attrval_spec 
    {
      temporal_changemodifydata.attrvalrecordlist()
        [AttrValRecord_Counter++] = temporal_AttrValRecord;
    }
|
;

%%

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

