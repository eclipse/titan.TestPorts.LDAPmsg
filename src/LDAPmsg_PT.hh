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
//  File:               LDAPmsg__PT.hh
//  Description:        LDAP test port header
//  Rev:                R9B
//  Prodnr:             CNL 113 385
//


#ifndef LDAPmsg__PT_HH
#define LDAPmsg__PT_HH

#include "LDAPmsg_PortType.hh"
#include "Abstract_Socket.hh"

#include "Lightweight_Directory_Access_Protocol_V3.hh"

namespace LDAPmsg__PortType {

#ifdef AS_USE_SSL
class LDAPmsg__PT : public SSL_Socket, public LDAPmsg__PT_BASE {
#else
class LDAPmsg__PT : public Abstract_Socket, public LDAPmsg__PT_BASE {
#endif
    
  public:
    LDAPmsg__PT(const char *par_port_name=NULL);
    ~LDAPmsg__PT();

    void set_parameter(const char *parameter_name, const char *parameter_value);

    void static LDAPMessage_std2LDAPMessage (Lightweight__Directory__Access__Protocol__V3::LDAPMessage& input);
    void static LDAPMessage2LDAPMessage_std(Lightweight__Directory__Access__Protocol__V3::LDAPMessage& input);

  protected:
    void user_map(const char *system_port);
    void user_unmap(const char *system_port);

    void user_start();
    void user_stop();

    void outgoing_send(const Lightweight__Directory__Access__Protocol__V3::LDAPMessage& send_par);
    void outgoing_send(const LDAPmsg__Types::ASP__LDAP__server& send_par);
    void outgoing_send(const LDAPmsg__Types::ASP__LDAP__connect& send_par);

    void message_incoming(const unsigned char*, int length, int client_id);
    void Add_Fd_Read_Handler(int fd) { Handler_Add_Fd_Read(fd); }
    void Add_Fd_Write_Handler(int fd) { Handler_Add_Fd_Write(fd); }
    void Remove_Fd_Read_Handler(int fd) { Handler_Remove_Fd_Read(fd); }
    void Remove_Fd_Write_Handler(int fd) { Handler_Remove_Fd_Write(fd); }
    void Remove_Fd_All_Handlers(int fd) { Handler_Remove_Fd(fd); }
    void Handler_Uninstall() { Uninstall_Handler(); }
    void Timer_Set_Handler(double call_interval, boolean is_timeout = TRUE,
      boolean call_anyway = TRUE, boolean is_periodic = TRUE) {
      Handler_Set_Timer(call_interval, is_timeout, call_anyway, is_periodic);
    }
    void client_connection_opened(int client_id);
    void peer_disconnected(int client_id);


    const char* local_port_name();
    const char* remote_address_name();
    const char* local_address_name();
    const char* remote_port_name();
    const char* halt_on_connection_reset_name();
    const char* server_mode_name();
    const char* socket_debugging_name();
    const char* nagling_name();
    const char* server_backlog_name();
    const char* ssl_use_ssl_name();
    const char* ssl_use_session_resumption_name();
    const char* ssl_private_key_file_name();
    const char* ssl_trustedCAlist_file_name();
    const char* ssl_certificate_file_name();
    const char* ssl_password_name();
    const char* ssl_cipher_list_name();
    const char* ssl_verifycertificate_name();


  private:
    void Handle_Fd_Event(int fd, boolean is_readable, boolean is_writable, boolean is_error);
    void Handle_Timeout(double time_since_last_call);

    TTCN_Buffer incoming_buffer;

    static bool has_binary_option (const Lightweight__Directory__Access__Protocol__V3::AttributeDescription& attdesc);
    

    void static Filter2Filter_std(Lightweight__Directory__Access__Protocol__V3::Filter& input);
    void static Filter_std2Filter (Lightweight__Directory__Access__Protocol__V3::Filter& input);

	void static AVA2AVA_std(Lightweight__Directory__Access__Protocol__V3::AttributeValueAssertion& input);
	void static AVA_std2AVA (Lightweight__Directory__Access__Protocol__V3::AttributeValueAssertion& input);

	void static AttributeList2AttributeList_std (Lightweight__Directory__Access__Protocol__V3::AttributeList& input);
	void static AttributeList_std2AttributeList (Lightweight__Directory__Access__Protocol__V3::AttributeList& input);
	
    void static unichar2oct (const UNIVERSAL_CHARSTRING& input, OCTETSTRING& output);
    void static oct2unichar (const OCTETSTRING& input, UNIVERSAL_CHARSTRING& output);

  };

} //namespace

#endif
