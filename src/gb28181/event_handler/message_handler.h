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
#include "gb28181/ptz/ptz_parser.h"
#include "gb28181/event_handler/sip_event.h"

#include <map>


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
    XmlParser                                          m_xmlparser;
    PtzParser                                          m_ptzparser;


    std::map<manscdp_devicecontrol_subcmd_e, BaseHandler::ptr> m_ctlhandler;  ///< control type

    std::map<manscdp_cmdtype_e, BaseHandler::ptr>            m_queryhandler;  ///< query type
    std::map<manscdp_cmdtype_e, BaseHandler::ptr>            m_notifyhandler;  ///< notify type
    std::map<manscdp_cmdtype_e, BaseHandler::ptr>            m_responsehandler;  ///< response type
};

}
