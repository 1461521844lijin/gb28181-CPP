#include "invite_request.h"
#include "application/dto/configs/MediaConfigDto.hpp"
#include "application/dto/configs/SipConfigDto.hpp"
#include "gb28181/request/requested_pool.h"
#include "gb28181/sip_server.h"
#include "glog/logging.h"
#include "oatpp/core/macro/component.hpp"
namespace GB28181 {

int InviteRequest::send_call(bool needcb) {
    auto excontext = g_SipServer::GetInstance()->GetExosipContext();
    if (nullptr == excontext) {
        LOG(ERROR) << "excontext is null";
        return -1;
    }

    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

    osip_message_t *msg  = nullptr;
    std::string     from = "sip:" + sipConfig->sipId + "@" + sipConfig->sipHost + ":" +
                       std::to_string(sipConfig->sipPort);
    std::string to =
        "sip:" + m_device->getDeviceId() + "@" + m_device->getIp() + ":" + m_device->getPort();

    exosip_guard guard(excontext);

    int ret = eXosip_call_build_initial_invite(excontext, 
                                                &msg, 
                                                to.c_str(), from.c_str(),
                                                nullptr, nullptr);
    if (ret) {
        LOG(ERROR) << "eXosip_call_build_initial_invite error:" << from << " " << to
                   << "  ret:" << ret;
        return -1;
    }

    std::string sdp_body = make_sdp_body();

    osip_message_set_body(msg, sdp_body.c_str(), sdp_body.length());
    osip_message_set_content_type(msg, "application/sdp");
    std::string session_exp = "1800;refresher=uac";
    osip_message_set_header(msg, "session-expires", session_exp.c_str());
    osip_message_set_supported(msg, "timer");

    int call_id = eXosip_call_send_initial_invite(excontext, msg);
    if (call_id > 0) {
        LOG(INFO) << "eXosip_call_send_initial_invite success: call_id=" << call_id;
    } else {
        LOG(ERROR) << "eXosip_call_send_initial_invite error: call_id=" << call_id;
    }

    LOG(INFO) << " send budy: \n" << sdp_body;

    if (needcb) {
        string reqid = get_reqid_from_request(msg);
        if (reqid.length() > 0) {
            BaseRequest::ptr req = shared_from_this();
            g_RequestedPool::GetInstance()->AddRequest(reqid, req);
        }
    }
}

const std::string InviteRequest::make_sdp_body() {
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);
    OATPP_COMPONENT(oatpp::Object<MediaConfigDto>, mediaConfig);

    std::stringstream sdp;
    sdp << "v=0\r\n";
    sdp << "o=" << sipConfig->sipId->c_str() << " 0 0 IN IP4 " << sipConfig->sipHost->c_str()
        << "\r\n";
    sdp << "s=Play\r\n";
    sdp << "c=IN IP4 " << mediaConfig->zlmAddr->c_str() << "\r\n";
    sdp << "t=0 0\r\n";
    sdp << "m=video " << m_rtp_port << " TCP/RTP/AVP 96 98 97\r\n";
    sdp << "a=recvonly\r\n";
    sdp << "a=rtpmap:96 PS/90000\r\n";
    sdp << "a=rtpmap:98 H264/90000\r\n";
    sdp << "a=rtpmap:97 MPEG4/90000\r\n";
    sdp << "a=setup:passive\r\n";
    sdp << "a=connection:new\r\n";
    sdp << "y=0100000001\r\n";
    sdp << "f=\r\n";

    return sdp.str();
}

}  // namespace GB28181
