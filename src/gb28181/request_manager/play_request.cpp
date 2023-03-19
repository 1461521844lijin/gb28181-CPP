#include "play_request.h"
#include "application/dto/configs/SipConfigDto.hpp"
#include "application/dto/configs/MediaConfigDto.hpp"
#include "gb28181/sip_server.h"
#include "glog/logging.h"
#include "oatpp/core/macro/component.hpp"
#include <iostream>
#include <sstream>

namespace GB28181 {

int PlayRequest::SendInviteRequest(Device::ptr device, eXosip_t *exconetxt) {
    if (exconetxt == nullptr) {
        exconetxt = g_SipServer::GetInstance()->GetExosipContext();
    }

    char session_exp[1024] = {0};
    // char from[1024]        = {0};
    // char to[1024]          = {0};
    char contact[1024] = {0};
    // char sdp[2048]     = {0};
    char head[1024]    = {0};

    osip_message_t *msg = nullptr;
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);
    OATPP_COMPONENT(oatpp::Object<MediaConfigDto>, mediaConfig);

    std::string from =
        "sip:" + sipConfig->sipId + "@" + sipConfig->sipHost + ":" + std::to_string(sipConfig->sipPort);
    std::string to =
        "sip:" + device->getDeviceId() + "@" + device->getIp() + ":" + device->getPort();

    std::stringstream sdp;
    sdp << "v=0\r\n";
    sdp << "o=" << sipConfig->sipId->c_str() << " 0 0 IN IP4 "<< sipConfig->sipHost->c_str() << "\r\n";
    sdp << "s=Play\r\n";
    sdp << "c=IN IP4 " << mediaConfig->zlmAddr->c_str() << "\r\n";
    sdp << "t=0 0\r\n";
    sdp << "m=video "<< mediaConfig->zlmRtpPort << " TCP/RTP/AVP 96 98 97\r\n";
    sdp << "a=recvonly\r\n";
    sdp << "a=rtpmap:96 PS/90000\r\n";
    sdp << "a=rtpmap:98 H264/90000\r\n";
    sdp << "a=rtpmap:97 MPEG4/90000\r\n";
    sdp << "a=setup:passive\r\n";
    sdp << "a=connection:new\r\n";
    sdp << "y=0100000001\r\n";
    sdp << "f=\r\n";

    // snprintf(sdp, 2048,
    //          "v=0\r\n"
    //          "o=%s 0 0 IN IP4 192.168.161.149\r\n"
    //          "s=Play\r\n"
    //          "c=IN IP4 %s\r\n"
    //          "t=0 0\r\n"
    //          "m=video 10000 TCP/RTP/AVP 96 98 97\r\n"
    //          "a=recvonly\r\n"
    //          "a=rtpmap:96 PS/90000\r\n"
    //          "a=rtpmap:98 H264/90000\r\n"
    //          "a=rtpmap:97 MPEG4/90000\r\n"
    //          "a=setup:passive\r\n"
    //          "a=connection:new\r\n"
    //          "y=0100000001\r\n"
    //          "f=\r\n",
    //          sipConfig->sipId->c_str(), "192.168.161.150", "192.168.161.150", 10000);

    LOG(INFO) << sdp.str() << "\n" << from << "\n" << to;

    int ret = eXosip_call_build_initial_invite(exconetxt, &msg, to.c_str(), from.c_str(), nullptr,
                                               nullptr);
    if (ret) {
        LOG(ERROR) << "eXosip_call_build_initial_invite error:" << from << " " << to
                   << "  ret:" << ret;
        return -1;
    }

    osip_message_set_body(msg, sdp.str().c_str(), sdp.str().size());
    osip_message_set_content_type(msg, "application/sdp");
    snprintf(session_exp, sizeof(session_exp) - 1, "%i;refresher=uac", 1800);
    osip_message_set_header(msg, "Session-Expires", session_exp);
    osip_message_set_supported(msg, "timer");
    // osip_message_set_header(msg, "Expires", 0);

    int call_id = eXosip_call_send_initial_invite(exconetxt, msg);

    if (call_id > 0) {
        LOG(INFO) << "eXosip_call_send_initial_invite success: call_id=" << call_id;
    } else {
        LOG(ERROR) << "eXosip_call_send_initial_invite error: call_id=" << call_id;
    }
    return ret;
}

int PlayRequest::SendByeRequest(Device::ptr device, eXosip_t *exconetxt) {
    if (exconetxt == nullptr) {
        exconetxt = g_SipServer::GetInstance()->GetExosipContext();
    }

    // 发送BYE请求
    eXosip_call_terminate(exconetxt, device->getCallId(), device->getDialogId());
}

}  // namespace GB28181