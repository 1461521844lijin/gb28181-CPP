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
#include <gb28181/request_manager/base_request.h>
#include <gb28181/request_manager/request_manager.h>
#include "request_sender.h"
#include "eXosip2/eXosip.h"
#include "glog/logging.h"
#include "gb28181/sip_server.h"

#include "oatpp/core/macro/component.hpp"
#include "application/dto/configs/SipConfigDto.hpp"
using  namespace std;


namespace GB28181 {

string g_sipfrom_ipport;
string g_sipfrom_domain;
string g_sipproxy_ipport;
string g_sipproxy_domain;
eXosip_t *g_excontext;

struct exosip_guard_t {
    explicit exosip_guard_t(eXosip_t* e) {
        m_excontext = e;
        eXosip_lock(m_excontext);
    }
    ~exosip_guard_t() {
        eXosip_unlock(m_excontext);
    }
    eXosip_t* m_excontext;
};

MsgSender::MsgSender()
{

}

MsgSender::~MsgSender()
{

}

int MsgSender::RegisterOnline(remote_sip_t &remote)
{
    osip_message_t * reg;

    exosip_guard_t guard(g_excontext);
    int rid = eXosip_register_build_initial_register(g_excontext,
            g_sipfrom_ipport.c_str(),
            g_sipproxy_ipport.c_str(),
            g_sipfrom_ipport.c_str(), 3600, &reg);
    if (rid < 1) {
        LOG(ERROR) << "build register failed, nRet: " << rid;
        return -1;
    }

    eXosip_add_authentication_info(g_excontext, remote.svr_id.c_str(), remote.svr_id.c_str(),
                                   remote.passwd.c_str(), "MD5", nullptr);

    int r = eXosip_register_send_register(g_excontext, rid, reg);
    if (r != 0) {
        LOG(ERROR) << "send register failed, ret: " << r;
        return -1;
    }
    return 0;
}

int MsgSender::Keepalive(remote_sip_t &remote, local_sip_t &local, bool bwait, BaseRequest::ptr &request)
{
    const char* cmd_type = "Keepalive";

    char body[1024];
    memset(body, 0x0, sizeof(body));
    string msg_sn = generate_sn();

    const char* pattern = "<?xml version=\"1.0\"?>\r\n"
                          "<Notify>\r\n"
                          "<CmdType>%s</CmdType>\r\n"
                          "<SN>%s</SN>\r\n"
                          "<DeviceID>%s</DeviceID>\r\n"
                          "<Status>OK</Status>\r\n"
                          "</Notify>\r\n";
    snprintf(body, sizeof(body), pattern, cmd_type, msg_sn.c_str(), local.svr_id.c_str());

    request = make_shared<KeepaliveRequest>(msg_sn);
    request->SetWait(bwait);
    int r = send_message(remote, body, request);
    if (r != 0) {
        return r;
    }
    return 0;
}


int MsgSender::CatalogQuery(Device::ptr device){


    auto excontext = g_SipServer::GetInstance()->GetExosipContext();
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

    osip_message_t * msg = nullptr;
    std::string from =
        "sip:" + sipConfig->sipId + "@" + sipConfig->sipHost + ":" + std::to_string(sipConfig->sipPort);
    std::string to =
        "sip:" + device->getDeviceId() + "@" + device->getIp() + ":" + device->getPort();


    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\"?>\r\n"
            << "<Query>\r\n"
            << "<CmdType>Catalog</CmdType>\r\n"
            << "<SN>" << 1 << "</SN>\r\n"
            << "<DeviceID>" << device->getDeviceId() << "</DeviceID>\r\n"
            << "</Query>\r\n";

    exosip_guard_t guard(excontext);
    int r = eXosip_message_build_request(excontext, &msg, "MESSAGE", to.c_str(), from.c_str(), nullptr);
    if (r != OSIP_SUCCESS) {
        LOG(ERROR) << "Build message request failed, sipto: " << to << ", ret: " << r;
        return -1;
    }

    osip_message_set_body(msg, manscdp.str().c_str(), manscdp.str().length());
    osip_message_set_content_type(msg, "Application/MANSCDP+xml");
    int rid = eXosip_message_send_request(excontext, msg);
    if (rid < 1) {
        LOG(ERROR) << "send message failed, ret: " << rid;
        return -1;
    }


    return 0;


}


string MsgSender::generate_sn()
{
    stringstream sn;
    sn << m_sn.fetch_add(1);
    return sn.str();
}

int MsgSender::send_message(remote_sip_t &remote, const char *body, BaseRequest::ptr &request)
{
    osip_message_t* msg = nullptr;

    exosip_guard_t guard(g_excontext);

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
            RequestManager::instance()->AddRequest(reqid, request);
        }
    }
    return 0;
}

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
