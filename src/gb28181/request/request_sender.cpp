/*
**	********************************************************************************
**
**	File		: msg_sender.cpp
**	Description	: 
**	Modify		: 2020/
 * 2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include <string>
#include <gb28181/request/base_request.h>
#include <gb28181/request/requested_pool.h>
#include "request_sender.h"
#include "eXosip2/eXosip.h"
#include "glog/logging.h"
#include "gb28181/sip_server.h"

#include "oatpp/core/macro/component.hpp"
#include "application/dto/configs/SipConfigDto.hpp"
using  namespace std;


namespace GB28181 {


MsgSender *MsgSender::instance()
{
    static MsgSender _ins;
    return &_ins;
}


MsgSender::MsgSender()
{

}

MsgSender::~MsgSender()
{

}

string MsgSender::generate_sn()
{
    stringstream sn;
    sn << m_sn.fetch_add(1);
    return sn.str();
}

/*
int MsgSender::send_message(remote_sip_t &remote, const char *body, BaseRequest::ptr &request)
{
    osip_message_t* msg = nullptr;

    exosip_guard guard(g_excontext);

    int r = eXosip_message_build_request(g_excontext, &msg, "MESSAGE",
            g_sipproxy_ipport.c_str(), g_sipfrom_ipport.c_str(), nullptr);
    if (r != OSIP_SUCCESS) {
        LOG(ERROR) << "Build message request failed, sipto: " << g_sipproxy_ipport << ", ret: " << r;
        return -1;
    }

    osip_message_set_body(msg, body, strlen(body));
    osip_message_set_content_type(msg, "Application/MANSCDP+xml");
    int tid = eXosip_message_send_request(g_excontext, msg);
    if (tid < 1) {
        LOG(ERROR) <<"Send message request failed, sipto: " << g_sipproxy_ipport << ", tid: " << tid;
        return -2;
    }

    string reqid = get_reqid_from_request(msg);
    if (request) {
        if (reqid.length() >0) {
            RequestedPool::instance()->AddRequest(reqid, request);
        }
    }
    return 0;
}
*/



const char *MsgSender::get_reqid_from_request(osip_message_t *msg)
{
    osip_generic_param_t* tag = nullptr;
    osip_to_get_tag(msg->from, &tag);
    if (nullptr == tag || nullptr == tag->gvalue) {
        return nullptr;
    }
    return (const char*) tag->gvalue;
}

}
