/*
**	********************************************************************************
**
**	File		: message_handler.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once


#include "base_handler.h"
#include "gb28181/manscdp/xml_parser.h"
#include "gb28181/manscdp/defs/defs.h"
#include "utils/ptz/ptz_parser.h"
#include "gb28181/event_handler/sip_event.h"


namespace GB28181 {

class MessageHandler : public BaseHandler
{
public:
    MessageHandler();

    ~MessageHandler() final = default;

    int HandleIncomingReq(const SipEvent::ptr& e);

    typedef function<int(const SipEvent::ptr&, tinyxml_doc_t&, manscdp_msgbody_header_t&)> msg_event_proc;

public:
    ///< handle response of outgoing request
    int HandleResponseSuccess(const SipEvent::ptr& e);
    int HandleResponseFailure(const SipEvent::ptr& e);

private:
    int handle_incoming_req_control(const SipEvent::ptr& e, tinyxml_doc_t& doc,
                                            manscdp_msgbody_header_t& bh);

    int handle_incoming_req_query(const SipEvent::ptr& e, tinyxml_doc_t& doc,
                                            manscdp_msgbody_header_t& bh);

    int handle_incoming_req_notify(const SipEvent::ptr& e, tinyxml_doc_t& doc,
                                   manscdp_msgbody_header_t& bh);

    int handle_incoming_req_response(const SipEvent::ptr& e, tinyxml_doc_t& doc,
                                            manscdp_msgbody_header_t& bh);

private:
    int on_devctrl_ptzcmd(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_teleboot(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_recordcmd(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_guardcmd(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_alarmcmd(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_iframecmd(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_dragzoomin(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_dragzoomout(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devctrl_homeposition(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);

private:
    int on_devcfg_basicparam(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devcfg_svacencodeconfig(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_devcfg_svacdeconfigconfig(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);

    int devctrl_subcmd(const SipEvent::ptr &e, string &devid, manscdp_devicecontrol_subcmd_e subcmd,
                       manscdp_switch_status_e onoff);

private:
    int on_query_device_status(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_catalog(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_device_info(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_record_info(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_alarm(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_config_download(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_preset_query(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);
    int on_query_mobile_position(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);

private:

    int on_notify_keepalive(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);

private:

    int on_response_catalog(const SipEvent::ptr& e, tinyxml_doc_t& doc, manscdp_msgbody_header_t& bh);


private:
    XmlParser                                          m_xmlparser;
    PtzParser                                          m_ptzparser;
    ///< control type
    map<manscdp_devicecontrol_subcmd_e, msg_event_proc> m_devctlproc;
    map<manscdp_deviceconfig_subcmd_e, msg_event_proc>  m_devcfgproc;

    ///< query type
    map<manscdp_cmdtype_e, msg_event_proc>              m_queryproc;

    /// notify type
    map<manscdp_cmdtype_e, msg_event_proc>              m_notifyproc;
    map<manscdp_cmdtype_e, BaseHandler::ptr>            m_notifyhandler;  ///< notify type

    ///< response type
    map<manscdp_cmdtype_e, msg_event_proc>              m_responseproc; 
};

}
