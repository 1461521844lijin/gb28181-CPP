/*
**	********************************************************************************
**
**	File		: base_request.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include "base_request.h"

#include "gb28181/sip_server.h"
#include "oatpp/core/macro/component.hpp"
#include "application/dto/configs/SipConfigDto.hpp"
#include "gb28181/request/requested_pool.h"
#include "Util/logger.h"

namespace GB28181 {






BaseRequest::~BaseRequest()= default;


int BaseRequest::HandleResponse(int statcode, tinxml_doc_ptr xml) {
    if (m_cb) {
        m_cb(statcode, std::move(xml));
    }
    return 0;
};


void BaseRequest::SetWait(bool bwait)
{
    m_bwait = bwait;
}

void BaseRequest::WaitResult()
{
    if (!m_bwait) return;
    unique_lock<mutex> lock(m_mutex);
    m_cond.wait(lock);
}

bool BaseRequest::IsFinished()
{
    return m_bfinished;
}

int BaseRequest::onRequestFinished()
{
    m_bfinished = true;
    if (m_bwait) {
        finished();
    }
    return 0;
}

void BaseRequest::finished()
{
    if (!m_bwait)
        return;

//    unique_lock<mutex> lock(m_mutex);
//    lock.unlock();
    m_cond.notify_one();
    m_bwait = false;
}

int BaseRequest::SetReqid(string &id)
{
    m_reqid = id;
    return 0;
}

time_t BaseRequest::GetReqtime()
{
    return m_reqtime;
}

const char *BaseRequest::get_reqid_from_request(osip_message_t *msg)
{
    osip_generic_param_t* tag = nullptr;
    osip_to_get_tag(msg->from, &tag);
    if (nullptr == tag || nullptr == tag->gvalue) {
        return nullptr;
    }
    return (const char*) tag->gvalue;
}


int MessageRequest::send_message(bool needcb){


    auto excontext = g_SipServer::GetInstance()->GetExosipContext();
    if(nullptr == excontext){
        ErrorL << "excontext is null";
        return -1;
    }
    auto reqsn = g_SipServer::GetInstance()->generate_sn();
    set_reqsn(reqsn);   
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);
   
    osip_message_t * msg = nullptr;
    std::string from =
        "sip:" + sipConfig->sipId + "@" + sipConfig->sipHost + ":" + std::to_string(sipConfig->sipPort);
    std::string to =
        "sip:" + m_device->getDeviceId() + "@" + m_device->getIp() + ":" + m_device->getPort();


    exosip_guard guard(excontext);
    int r = eXosip_message_build_request(excontext, &msg, "MESSAGE", to.c_str(), from.c_str(), nullptr);
    if (r != OSIP_SUCCESS) {
        ErrorL << "Build message request failed, sipto: " << to << ", ret: " << r;
        return -1;
    }
    std::string body = make_manscdp_body();
    osip_message_set_body(msg, body.c_str(), body.length());
    osip_message_set_content_type(msg, "Application/MANSCDP+xml");
    int rid = eXosip_message_send_request(excontext, msg);
    if (rid < 1) {
        ErrorL << "send message failed, ret: " << rid;
        return -1;
    }

    DebugL <<" send budy \n" <<body;

    // 请求发送成功后，将请求id保存在请求池，等待回复和回调处理
    if (needcb) {
         string reqid = get_reqid_from_request(msg);
        if (reqid.length() >0) {
            BaseRequest::ptr req = shared_from_this();
            g_RequestedPool::GetInstance()->AddRequest(reqid, req);
        }
    }
    return 0;
}

}

