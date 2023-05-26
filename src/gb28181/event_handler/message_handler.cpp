/*
**	********************************************************************************
**
**	File		: message_handler.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include <gb28181/request/requested_pool.h>
#include "message_handler.h"
#include "osipparser2/osip_const.h"
#include "Util/logger.h"

#include "gb28181/device/deviceManager.h"
#include "utils/CommonTools.h"

#include "gb28181/event_handler/message/notify/keepalive_handler.h"
#include "gb28181/event_handler/message/notify/alarm_handler.h"

#include "gb28181/event_handler/message/response/catalog_handler.h"
#include "gb28181/event_handler/message/response/preset_handler.h"
#include "gb28181/event_handler/message/response/guard_handler.h"


namespace GB28181 {

#define MSGPROC_TEMPLATE(F) (bind(&MessageHandler::F, this, placeholders::_1, placeholders::_2, placeholders::_3))

MessageHandler::MessageHandler()
{
    
    m_notifyhandler.insert(make_pair(MANSCDP_NOTIFY_CMD_KEEPALIVE, new KeepaliveHandler));
    m_notifyhandler.insert(make_pair(MANSCDP_NOTIFY_CMD_ALARM, new AlarmHandler));


    m_responsehandler.insert(make_pair(MANSCDP_QUERY_CMD_CATALOG, new CatalogHandler));
    m_responsehandler.insert(make_pair(MANSCDP_QUERY_CMD_PRESET_QUERY, new PresetQuireHandler));
    m_responsehandler.insert(make_pair(MANSCDP_RESOPNSE_CMD_DEVICE_GUARD, new GuardHandler));
}

int MessageHandler::HandleIncomingReq(const SipEvent::ptr &e)
{

    const char* username = e->exevent->request->from->url->username;
    const char* host = e->exevent->request->from->url->host;

    osip_body_t* body = nullptr;
    osip_message_get_body(e->exevent->request, 0, &body);
    if (body == nullptr) {
        sendSimplyResp(username, e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
        return -1;
    }
    int r;

    // InfoL << "incoming request body: " << body->body;

    // tinyxml_doc_t doc;
    tinxml_doc_ptr doc = std::make_shared<tinyxml2::XMLDocument>();
    r = m_xmlparser.Load(body->body, body->length, doc);
    if (r !=0) {
        sendSimplyResp(username, e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
    }

    manscdp_msgbody_header_t bodyheader;
    r = m_xmlparser.ParseXmlHeader(doc, bodyheader);
    if (r !=0) {
        sendSimplyResp(username, e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
        return r;
    }

    // InfoL << "Revice message, category: " << bodyheader.cmd_category <<", cmd_type: "
    //         << bodyheader.cmd_type << " from "<<username << ", host: "<< host;

    switch (bodyheader.cmd_category)
    {
        case MANSCDP_CMD_CATEGORY_CONTROL:
            r = handle_incoming_req_control(e, doc, bodyheader);
            break;
        case MANSCDP_CMD_CATEGORY_QUERY:
            r = handle_incoming_req_query(e, doc, bodyheader);
            break;
        case MANSCDP_CMD_CATEGORY_NOTIFY:
            r = handle_incoming_req_notify(e, doc, bodyheader);
            break;
        case MANSCDP_CMD_CATEGORY_RESPONSE:
            r = handle_incoming_req_response(e, doc, bodyheader);
            break;
        default:
            break;
    }
    return 0;
}

int MessageHandler::HandleResponseSuccess(const SipEvent::ptr &e)
{
    // osip_body_t* body = nullptr;
    // osip_message_get_body(e->exevent->response, 0, &body);
    // if (body == nullptr) {
    //     sendSimplyResp("recive answered", e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
    //     return -1;
    // }
    // int r;

    // InfoL << "incoming response body: " << body->body;



    int statcode = getStatcodeFromResp(e->exevent->response);
    string reqid = getMsgIdFromReq(e->exevent->request);
    InfoL << "response reqid = " << reqid;

    g_RequestedPool::GetInstance()->HandleMsgResponse(reqid, statcode);
    return 0;
}

int MessageHandler::HandleResponseFailure(const SipEvent::ptr &e)
{
    HandleResponseSuccess(e);
    return 0;
}

int MessageHandler::handle_incoming_req_control(const SipEvent::ptr &e, tinxml_doc_ptr &doc,
                                                 manscdp_msgbody_header_t &bh)
{
    // if (bh.cmd_type == MANSCDP_CONTROL_CMD_DEVICE_CONTROL) {
    //     for (auto cmd : bh.devctl_subcmd) {
    //         m_devctlproc[cmd](e, doc, bh);
    //     }
    // }
    // else if (bh.cmd_type == MANSCDP_CONTROL_CMD_DEVICE_CONFIG) {
    //     for (auto cmd : bh.devcfg_subcmd) {
    //         m_devcfgproc[cmd](e, doc, bh);
    //     }
    // }
    return 0;
}

int MessageHandler::handle_incoming_req_query(const SipEvent::ptr &e, tinxml_doc_ptr &doc,
                                               manscdp_msgbody_header_t &bh)
{
    // auto proc = m_queryproc.find(bh.cmd_type);
    // if (proc == m_queryproc.end()) {
    //     WarnL << "Not found proc, cmd_type: " << bh.cmd_type;
    //     sendSimplyResp(e->name, e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
    //     return -1;
    // }
    // m_queryproc[bh.cmd_type](e, doc, bh);
    return 0;
}

int MessageHandler::handle_incoming_req_notify(const SipEvent::ptr &e, tinxml_doc_ptr &doc,
                                                manscdp_msgbody_header_t &bh)
{
    auto handler = m_notifyhandler.find(bh.cmd_type);
    if (handler == m_notifyhandler.end()) {
        WarnL << "Not found proc, cmd_type: " << bh.cmd_type;
        sendSimplyResp(e->name, e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
        return -1;
    }
    
    handler->second->handle(e, doc);
    return 0;
    
    

    return 0;
}

int MessageHandler::handle_incoming_req_response(const SipEvent::ptr &e, tinxml_doc_ptr &doc,
                                                  manscdp_msgbody_header_t &bh)
{




    auto handler = m_responsehandler.find(bh.cmd_type);
    if (handler == m_responsehandler.end()) {
       
        auto req = g_RequestedPool::GetInstance()->GetMsgRequestBySn(bh.sn);
        if(req){ 
            req->HandleResponse(200, doc);
            return 0;
        }
        WarnL << "Not found proc, cmd_type: " << bh.cmd_type;
        sendSimplyResp(e->name, e->excontext, e->exevent->tid, SIP_BAD_REQUEST);
        return -1;
    }
    handler->second->handle(e, doc);
    return 0;
}



}
