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
//  File:               LDAPmsg_PT.cc
//  Description:        LDAP test port source code
//  Rev:                R9B
//  Prodnr:             CNL 113 385
//


#include <ctype.h>
#include "LDAPmsg_PT.hh" 
using namespace Lightweight__Directory__Access__Protocol__V3;
namespace LDAPmsg__PortType {



LDAPmsg__PT::LDAPmsg__PT(const char *par_port_name)
    
#ifdef AS_USE_SSL
  : SSL_Socket("LDAP", par_port_name)
#else
  : Abstract_Socket("LDAP", par_port_name)
#endif  
  , LDAPmsg__PT_BASE(par_port_name)
{
  set_ttcn_buffer_usercontrol(true);
}

LDAPmsg__PT::~LDAPmsg__PT()
{

}

const char* LDAPmsg__PT::local_port_name()              { return "local_port";}
const char* LDAPmsg__PT::remote_address_name()          { return "remote_address";}
const char* LDAPmsg__PT::local_address_name()           { return "local_address";} // not used in the tesport
const char* LDAPmsg__PT::remote_port_name()             { return "remote_port";}
const char* LDAPmsg__PT::halt_on_connection_reset_name(){ return "halt_on_connection_reset";}
const char* LDAPmsg__PT::server_mode_name()             { return "server_mode";}
const char* LDAPmsg__PT::socket_debugging_name()        { return "socket_debugging";}
const char* LDAPmsg__PT::nagling_name()                 { return "nagling";}
const char* LDAPmsg__PT::server_backlog_name()          { return "server_backlog";}
const char* LDAPmsg__PT::ssl_use_ssl_name()                { return "ssl_use_ssl";}
const char* LDAPmsg__PT::ssl_use_session_resumption_name() { return "ssl_use_session_resumption";}
const char* LDAPmsg__PT::ssl_private_key_file_name()       { return "ssl_private_key_file";}
const char* LDAPmsg__PT::ssl_trustedCAlist_file_name()     { return "ssl_trustedCAlist_file";}
const char* LDAPmsg__PT::ssl_certificate_file_name()       { return "ssl_certificate_chain_file";}
const char* LDAPmsg__PT::ssl_password_name()               { return "ssl_private_key_password";}
const char* LDAPmsg__PT::ssl_cipher_list_name()            { return "ssl_allowed_ciphers_list";}
const char* LDAPmsg__PT::ssl_verifycertificate_name()      { return "ssl_verify_certificate";}

void LDAPmsg__PT::set_parameter(const char *parameter_name,
        const char *parameter_value)
{
  log_debug("entering LDAPmsg__PT::set_parameter(%s, %s)", parameter_name, parameter_value);
  if(!parameter_set(parameter_name ,parameter_value)) {
    log_warning("LDAPmsg__PT::set_parameter(): Unsupported Test Port parameter: %s", parameter_name);
  }
  log_debug("leaving LDAPmsg__PT::set_parameter(%s, %s)", parameter_name, parameter_value);
}

void LDAPmsg__PT::Handle_Fd_Event(int fd,
  boolean is_readable, boolean is_writable, boolean is_error)
{
  log_debug("entering LDAPmsg__PT::Handle_Fd_Event()");
  Handle_Socket_Event(fd, is_readable, is_writable, is_error);
  log_debug("leaving LDAPmsg__PT::Handle_Fd_Event()");
}

void LDAPmsg__PT::Handle_Timeout(double time_since_last_call)
{
  log_debug("entering LDAPmsg__PT::Handle_Timeout()");
  Handle_Timeout_Event(time_since_last_call);
  log_debug("leaving LDAPmsg__PT::Handle_Timeout()");
}

void LDAPmsg__PT::message_incoming(const unsigned char* /*msg*/, int /*messageLength*/, int client_id) {
  log_debug("entering LDAPmsg__PT::message_incoming()");

  TTCN_Buffer * buf_p = get_buffer(client_id);
  
  while (buf_p->contains_complete_TLV()) {
    log_debug("Incoming buffer has been filled with a complete TLV");
    LDAPMessage msg;
    msg.decode(LDAPMessage_descr_, *buf_p, TTCN_EncDec::CT_BER, BER_ACCEPT_ALL);
    buf_p->cut();
    LDAPMessage_std2LDAPMessage(msg);
    if (get_server_mode()) {
      LDAPmsg__Types::ASP__LDAP__server parameters_ASP_LDAP;
      parameters_ASP_LDAP.data() = msg;
      if(client_id != -1) {
        parameters_ASP_LDAP.client__id() = client_id;
      } else {
        parameters_ASP_LDAP.client__id() = OMIT_VALUE;
      }
      incoming_message(parameters_ASP_LDAP);
    } else {
      incoming_message(msg);
    }
  } 

  log_debug("leaving LDAPmsg__PT::message_incoming()");
}

void LDAPmsg__PT::user_map(const char */*system_port*/)
{
  log_debug("entering LDAPmsg__PT::user_map()");
  map_user();

  log_debug("leaving LDAPmsg__PT::user_map()");
}

void LDAPmsg__PT::user_unmap(const char */*system_port*/)
{
  log_debug("entering LDAPmsg__PT::user_unmap()");
  unmap_user();
  log_debug("leaving LDAPmsg__PT::user_unmap()");
}

void LDAPmsg__PT::user_start()
{
}

void LDAPmsg__PT::user_stop()
{
}

void LDAPmsg__PT::outgoing_send(const LDAPMessage& send_par)
{
  log_debug("entering LDAPmsg__PT::outgoing_send()");
  
  LDAPMessage msg_copy = send_par;
  LDAPMessage2LDAPMessage_std(msg_copy);
   
  if (get_server_mode())
    log_error("The LDAPMessage structure cannot be sent on the port in server mode");

  TTCN_Buffer buf;
  msg_copy.encode(LDAPMessage_descr_, buf, TTCN_EncDec::CT_BER,
     BER_ENCODE_DER);

  send_outgoing(buf.get_data(), buf.get_len());

  log_debug("leaving LDAPmsg__PT::outgoing_send()");
}

void LDAPmsg__PT::outgoing_send(const LDAPmsg__Types::ASP__LDAP__server& send_par)
{
  log_debug("entering LDAPmsg__PT::outgoing_send()");

  LDAPmsg__Types::ASP__LDAP__server msg_copy = send_par;
  LDAPMessage2LDAPMessage_std(msg_copy.data());

  if (!get_server_mode())
    log_error("The ASP_LDAP_server structure cannot be sent on the port in client mode");

  TTCN_Buffer buf;
  msg_copy.data().encode(LDAPMessage_descr_, buf, TTCN_EncDec::CT_BER,
     BER_ENCODE_DER);

  if(msg_copy.client__id().ispresent()) {
    send_outgoing(buf.get_data(), buf.get_len(), msg_copy.client__id()());
  } else {
    send_outgoing(buf.get_data(), buf.get_len());
  }

  log_debug("leaving LDAPmsg__PT::outgoing_send()");
}

void LDAPmsg__PT::outgoing_send(const LDAPmsg__Types::ASP__LDAP__connect& send_par)
{
    log_debug("entering LDAPasp__RFC4511__PT::"
                        "outgoing_send(ASP__LDAP__connect)");

    char remotePort[6];
    char localPort[6];
    const char* localHostname = NULL;
    const char* remoteHostname = NULL;
    char* localServicename = NULL;

    if(send_par.hostname().ispresent()){
       remoteHostname = (const char* )send_par.hostname()();
    } else {
       remoteHostname = get_remote_host_name();
    }
    if(send_par.portnumber().ispresent()){
      sprintf(remotePort, "%d", (int)send_par.portnumber()());
    } else {
      sprintf(remotePort, "%d", (int)get_remote_port_number());
    }

    if(send_par.local__hostname().is_bound() && 
                        send_par.local__hostname().ispresent()){
      localHostname = send_par.local__hostname()();
    } else {
      localHostname = get_local_host_name();
      if(localHostname){
                log_debug("using local host name configured in %s: %s",
                                local_address_name(), localHostname);
      } else {
        log_debug("using 'localhost' as local host name");
      }
    }

    if(send_par.local__portnumber().is_bound() && 
                        send_par.local__portnumber().ispresent()) {
      sprintf(localPort, "%d", (int)send_par.local__portnumber()());
      localServicename = localPort;
    } else if(get_local_port_number() > 0) {
      log_debug("using local port number configured in %s: %d",
                                local_port_name(), get_local_port_number());
      sprintf(localPort, "%d", get_local_port_number());
      localServicename = localPort;
    } else {
      log_debug("using random local port number");
    }

    if(!get_server_mode()){  // in client mode, the connect means reconnect
      remove_all_clients(); // so just close it if active
    }
    
    open_client_connection(remoteHostname, remotePort, localHostname, localServicename);

    log_debug("leaving LDAPasp__RFC4511__PT::"
                        "outgoing_send(ASP__LDAP__connect)");

}

void LDAPmsg__PT::client_connection_opened(int client_id){

        log_debug("entering LDAPmsg__PT::client_connection_opened(%d)",
                        client_id);

        if(get_use_connection_ASPs())
        {
                LDAPmsg__Types::ASP__LDAP__connect__result message_incoming;

                message_incoming.client__id() = client_id;
                incoming_message(message_incoming);
        }
        else Abstract_Socket::client_connection_opened(client_id);
        log_debug("leaving LDAPmsg__PT::client_connection_opened(%d)",
                        client_id);

}
void LDAPmsg__PT::peer_disconnected(int client_id)
{
        log_debug("entering LDAPmsg__PT::peer_disconnected()");

        if (get_use_connection_ASPs()){
            LDAPmsg__Types::ASP__LDAP__closed message_incoming;

            message_incoming.client__id() = client_id;

            incoming_message(message_incoming);
        }
        else Abstract_Socket::peer_disconnected(client_id);
        log_debug("leaving LDAPmsg__PT::peer_disconnected()");
}

bool LDAPmsg__PT::has_binary_option (const UNIVERSAL_CHARSTRING& attdesc) {

  bool has_binary=false;
  char* outbuf = new char[attdesc.lengthof()+1];

  const universal_char* inbuf = (const universal_char*)attdesc;

  for (int cur_char = 0; cur_char < attdesc.lengthof(); cur_char++) {
    if (inbuf[cur_char].uc_group != (char)0 &&
  inbuf[cur_char].uc_plane != (char)0 &&
  inbuf[cur_char].uc_row != (char) 0) // non-ASCII character
      outbuf[cur_char] = '?'; // it will be substituted with questionmark
    else
      outbuf[cur_char] = toupper(inbuf[cur_char].uc_cell);
  }
  outbuf[attdesc.lengthof()] = '\0';
  if (strstr(outbuf, ";BINARY")!=NULL) has_binary=true;
   
  delete [] outbuf;
  return has_binary;
}

void LDAPmsg__PT::LDAPMessage_std2LDAPMessage (LDAPMessage& input) {

  switch (input.protocolOp().get_selection()) {

  case ProtocolOp::ALT_searchRequest: {
  SearchRequest& in = input.protocolOp().searchRequest();
    Filter_std2Filter (in.filter());
  }
  break;
  case ProtocolOp::ALT_searchResEntry:{
    SearchResultEntry& in = input.protocolOp().searchResEntry();
    for (int i = 0; i < in.attributes().size_of(); i++) {
      bool binary = has_binary_option(in.attributes()[i].typeField());
      for (int j = 0; j < in.attributes()[i].vals().size_of(); j++) {
        if (!binary) {
          UNIVERSAL_CHARSTRING unicharval;
          oct2unichar((const OCTETSTRING&)in.attributes()[i].vals()[j].binary(), unicharval);
          in.attributes()[i].vals()[j].string() = unicharval;
        }
      }
    }
  }
  break;
  case ProtocolOp::ALT_modifyRequest: {
    ModifyRequest& in = input.protocolOp().modifyRequest();
    for (int i = 0; i < in.modification().size_of(); i++) {
      bool binary_attribute = has_binary_option(in.modification()[i].modification().typeField());
      for (int j = 0; j < in.modification()[i].modification().vals().size_of(); j++) {
        if (!binary_attribute) {
          UNIVERSAL_CHARSTRING unicharval;
          oct2unichar((const OCTETSTRING&)in.modification()[i].modification().vals()[j].binary(), unicharval);
          in.modification()[i].modification().vals()[j].string() = unicharval;
        }
      }
    }
  }
  break;
  case ProtocolOp::ALT_addRequest:{
    AddRequest& in = input.protocolOp().addRequest();
    AttributeList_std2AttributeList(in.attributes());
  }
  break;
  case ProtocolOp::ALT_compareRequest: {
    CompareRequest& in = input.protocolOp().compareRequest();
    AVA_std2AVA(in.ava());
  }
  break;
  default: // no change necessary
    {}
  }
}

void LDAPmsg__PT::Filter_std2Filter(Filter& input) {
   
  switch (input.get_selection()) {
  case Filter::ALT_andField: {
  for (int i = 0; i < input.andField().size_of(); i++) {
    Filter_std2Filter(input.andField()[i]);
    }
  }
    break;
  case Filter::ALT_orField: {
  for (int i = 0; i < input.orField().size_of(); i++)
    Filter_std2Filter(input.orField()[i]);
  }
  break;
  case Filter::ALT_notField: {
    Filter_std2Filter(input.notField());
  }
  break;
  case Filter::ALT_equalityMatch:{
    AVA_std2AVA(input.equalityMatch());
  }
  break;
  case Filter::ALT_greaterOrEqual: {
    AVA_std2AVA (input.greaterOrEqual());
  }
  break;
  case Filter::ALT_lessOrEqual: {
    AVA_std2AVA(input.lessOrEqual());
  }
  break;
  case Filter::ALT_approxMatch: {
    AVA_std2AVA(input.approxMatch());
  }
  break;
  case Filter::ALT_extensibleMatch: {
    UNIVERSAL_CHARSTRING unicharval;
    if (input.extensibleMatch().typeField().ispresent()) {
      AttributeDescription& attdesc = 
        (AttributeDescription&)input.extensibleMatch().typeField();
      if (!has_binary_option((const UNIVERSAL_CHARSTRING&)attdesc)) {
        oct2unichar((const OCTETSTRING&)input.extensibleMatch().matchValue().binary(), unicharval);
        input.extensibleMatch().matchValue().string() = unicharval;
      }
    } else { // no attribute description present, we assume string input - hopefully it can be interpreted as UTF8String
      oct2unichar((const OCTETSTRING&)input.extensibleMatch().matchValue().binary(), unicharval);
      input.extensibleMatch().matchValue().string() = unicharval;
    }
  }
  break;
  default:  // nothing to convert
    {}
  }
}

void LDAPmsg__PT::AVA_std2AVA (AttributeValueAssertion& input) {
  if (!has_binary_option((const UNIVERSAL_CHARSTRING&)input.attributeDesc())) {
    UNIVERSAL_CHARSTRING unicharval;
    oct2unichar((const OCTETSTRING&)input.assertionValue().binary(), unicharval);    
    input.assertionValue().string() = unicharval;
  }
}

void LDAPmsg__PT::oct2unichar (const OCTETSTRING& input, UNIVERSAL_CHARSTRING& output) {
  TTCN_Buffer buf;
  input.encode(OCTETSTRING_descr_, buf, TTCN_EncDec::CT_BER, BER_ENCODE_DER);
   
  output.decode (OctetStringLike__UniCharString_descr_, buf, TTCN_EncDec::CT_BER,
     BER_ACCEPT_ALL);
}

void LDAPmsg__PT::LDAPMessage2LDAPMessage_std(LDAPMessage& input) {

  switch (input.protocolOp().get_selection()) {

  case ProtocolOp::ALT_searchRequest: {
    SearchRequest& in = input.protocolOp().searchRequest();
    Filter2Filter_std(in.filter());
  }
  break;
   
  case ProtocolOp::ALT_searchResEntry: {
    SearchResultEntry& in = input.protocolOp().searchResEntry();
    for (int i = 0; i < in.attributes().size_of(); i++) {
    for (int j = 0; j < in.attributes()[i].vals().size_of(); j++) {
        switch (in.attributes()[i].vals()[j].get_selection()) {
      case AttributeValue::ALT_string: {
        if (has_binary_option((const UNIVERSAL_CHARSTRING&)in.attributes()[i].typeField()))
          TTCN_warning("AttributeValue contains UTF8String data"
            " and the attributeDescription contains binary option.");
        OCTETSTRING octval;
        unichar2oct((const UNIVERSAL_CHARSTRING&)in.attributes()[i].vals()[j].string(), octval);
          in.attributes()[i].vals()[j].binary() = octval;
      }
      break;
      case AttributeValue::ALT_binary:
        if (! has_binary_option(in.attributes()[i].typeField()))
          TTCN_warning("AttributeValue contains OCTET STRING data "
              "and the attributeDescription does not contain binary option.");
      break;
      default:
        TTCN_error("Invalid union element in AttributeValue.");
      }
    }
  }
  }
  break;
  case ProtocolOp::ALT_modifyRequest: {
    ModifyRequest& in = input.protocolOp().modifyRequest();
    for (int i = 0; i < in.modification().size_of(); i++) {
      for (int j = 0; j < in.modification()[i].modification().vals().size_of(); j++) {

        switch (in.modification()[i].modification().vals()[j].get_selection()) {
        case AttributeValue::ALT_string: {
          if (has_binary_option((const UNIVERSAL_CHARSTRING&)in.modification()[i].modification().typeField()))
            TTCN_warning("AttributeValue contains UTF8String data "
              "and the attributeDescription contains binary option.");
          OCTETSTRING octval;
          unichar2oct((const UNIVERSAL_CHARSTRING&)in.modification()[i].modification().vals()[j].string(), octval);
          in.modification()[i].modification().vals()[j].binary() = octval;
        }
        break;
        case AttributeValue::ALT_binary:
          if (! has_binary_option((const UNIVERSAL_CHARSTRING&)in.modification()[i].modification().typeField()))
            TTCN_warning("AttributeValue contains OCTET STRING data "
              "and the attributeDescription does not contain binary option.");
        break;
        default:
          TTCN_error("Invalid union element in AttributeValue");
        }
      }
    }
  }
  break;
  case ProtocolOp::ALT_addRequest: {
    AddRequest& in = input.protocolOp().addRequest();
    AttributeList2AttributeList_std(in.attributes());
  }
  break;
  case ProtocolOp::ALT_compareRequest: {
    CompareRequest& in = input.protocolOp().compareRequest();
    AVA2AVA_std(in.ava());
  }
  break;
  default: // no conversion necessary
    {}
  }
}

void LDAPmsg__PT::AttributeList_std2AttributeList (AttributeList& input) {
  for (int i = 0; i < input.size_of(); i++) {
    bool binary_attribute = has_binary_option(input[i].typeField());
    for (int j = 0; j < input[i].vals().size_of(); j++) {
      if (!binary_attribute) {
        UNIVERSAL_CHARSTRING unicharval;
        oct2unichar(input[i].vals()[j].binary(), unicharval);
        input[i].vals()[j].string() = unicharval;
      }
    }
  }
}


void LDAPmsg__PT::AttributeList2AttributeList_std (AttributeList& input) {
  for (int att = 0; att < input.size_of(); att++) {
    for (int i = 0; i < input[att].vals().size_of(); i++) {
      switch (input[att].vals()[i].get_selection()) {
      case AttributeValue::ALT_string: {
        if (has_binary_option(input[att].typeField()))
          TTCN_warning("AttributeValue contains UTF8String data "
            "and the type contains binary option.");
          OCTETSTRING octval;
          unichar2oct(input[att].vals()[i].string(), octval);
          input[att].vals()[i].binary() = octval;
          
      }
      break;
      case AttributeValue::ALT_binary:
        if (! has_binary_option(input[att].typeField()))
          TTCN_warning("AttributeValue contains OCTET STRING data "
            "and the type does not contain binary option.");
      break;
      default:
        TTCN_error("Invalid union element in AttributeValue");
      }
    }
  }
}


void LDAPmsg__PT::Filter2Filter_std(Filter& input) {
  switch (input.get_selection()) {
  case Filter::ALT_andField: {
    for (int i = 0; i < input.andField().size_of(); i++) {
      Filter2Filter_std(input.andField()[i]);
    }
  }
  break;
  case Filter::ALT_orField: {
    for (int i = 0; i < input.orField().size_of(); i++) {
      Filter2Filter_std(input.orField()[i]);
    }
  }
  break;
  case Filter::ALT_notField: {
    Filter2Filter_std(input.notField());
  }
  break;
  case Filter::ALT_equalityMatch: {
    AVA2AVA_std(input.equalityMatch());
  }
  break;
  case Filter::ALT_greaterOrEqual: {
    AVA2AVA_std(input.greaterOrEqual());   
  }
  break;
  case Filter::ALT_lessOrEqual: {
    AVA2AVA_std(input.lessOrEqual());
  }
  break;
  case Filter::ALT_approxMatch: {
    AVA2AVA_std(input.approxMatch());
  }
  break;
  case Filter::ALT_extensibleMatch: {
    const bool binary_option = has_binary_option((const UNIVERSAL_CHARSTRING&)input.extensibleMatch().typeField()());
    
    switch (input.extensibleMatch().matchValue().get_selection()) {
    case AssertionValue::ALT_binary: {
      if (!binary_option)
        TTCN_warning("MatchingRuleAssertion contains binary matchValue "
          "and typeField does not contain binary option.");
    }
    break;
    case AssertionValue::ALT_string: {
      if (binary_option)
        TTCN_warning("MatchingRuleAssertion contains string matchValue "
          "and typeField contains binary option.");
      OCTETSTRING octval;
      unichar2oct(input.extensibleMatch().matchValue().string(), octval);
      input.extensibleMatch().matchValue().binary() = octval;
    }
    break;
    default:
      TTCN_error("Invalid union value in AssertionValue.");
    }
  }
  break;
  default: // no conversion necessary
    {}
  }
}

void LDAPmsg__PT::AVA2AVA_std(AttributeValueAssertion& input) {
   
  switch (input.assertionValue().get_selection()) {
  case AssertionValue::ALT_string: {
    OCTETSTRING octval;
    unichar2oct(input.assertionValue().string(), octval);
    input.assertionValue().binary() = octval;
    if (has_binary_option((const UNIVERSAL_CHARSTRING&)input.attributeDesc()))
      TTCN_warning("AssertionValue contains UTF8String data and the attributeDescription contains binary option.");
  }
  break;
  case AssertionValue::ALT_binary:
    if (! has_binary_option((const UNIVERSAL_CHARSTRING&)input.attributeDesc()))
      TTCN_warning("AssertionValue contains OCTET STRING data and the attributeDescription does not contain binary option.");
  break;
  default:
    TTCN_error("Invalid union element in AttributeValueAssertion.");
  }
}



void LDAPmsg__PT::unichar2oct (const UNIVERSAL_CHARSTRING& input, OCTETSTRING& output) {
  TTCN_Buffer buf;
  input.encode(OctetStringLike__UniCharString_descr_, buf, TTCN_EncDec::CT_BER,
         BER_ENCODE_DER);
  output.decode(OCTETSTRING_descr_, buf, TTCN_EncDec::CT_BER, BER_ACCEPT_ALL);
}

}//namespace

namespace LDAPmsg__Types{
INTEGER f__decode__LDAPMessage(const OCTETSTRING& data, LDAPMessage& pdu){
  TTCN_Buffer buf = TTCN_Buffer(data);

  if (buf.contains_complete_TLV()) {
    pdu.decode(LDAPMessage_descr_, buf, TTCN_EncDec::CT_BER, BER_ACCEPT_ALL);
    LDAPmsg__PortType::LDAPmsg__PT::LDAPMessage_std2LDAPMessage(pdu);
    return buf.get_pos();
  } 


  return -1;
}

OCTETSTRING f__encode__LDAPMessage(const LDAPMessage& pdu){
  LDAPMessage msg_copy = pdu;
  LDAPmsg__PortType::LDAPmsg__PT::LDAPMessage2LDAPMessage_std(msg_copy);
  TTCN_Buffer buf;
  msg_copy.encode(LDAPMessage_descr_, buf, TTCN_EncDec::CT_BER,
     BER_ENCODE_DER);

  OCTETSTRING ret_val;
  buf.get_string(ret_val);
  return ret_val;
}
  
}
