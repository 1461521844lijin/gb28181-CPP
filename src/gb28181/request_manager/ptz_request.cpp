#include "ptz_request.h"

#include "gb28181/ptz/ptz_cmd.h"

#include "gb28181/sip_server.h"
#include "oatpp/core/macro/component.hpp"
#include "application/dto/configs/SipConfigDto.hpp"

namespace GB28181 {


int PtzRequest::SendPtzRequest(Device::ptr device,
                               int         leftRight,
                               int         upDown,
                               int         inOut,
                               int         moveSpeed,
                               int         zoomSpeed) 
{


    auto excontext = g_SipServer::GetInstance()->GetExosipContext();
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

    osip_message_t * msg = nullptr;
    std::string from =
        "sip:" + sipConfig->sipId + "@" + sipConfig->sipHost + ":" + std::to_string(sipConfig->sipPort);
    std::string to =
        "sip:" + device->getDeviceId() + "@" + device->getIp() + ":" + device->getPort();

    std::string ptzCmd = PtzCmd::cmdString(leftRight, upDown, inOut, moveSpeed, zoomSpeed);

    std::stringstream manscdp;
    manscdp << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    manscdp << "<Control>\r\n";
    manscdp << "<CmdType>DeviceControl</CmdType>\r\n";
    manscdp << "<SN>2</SN>\r\n"; 
    manscdp << "<DeviceID>" << device->getDeviceId() << "</DeviceID>\r\n";
    manscdp << "<PTZCmd>" << ptzCmd << "</PTZCmd>\r\n";
    manscdp << "</Control>\r\n";

    eXosip_lock(excontext);
    int r = eXosip_message_build_request(excontext, &msg, "MESSAGE", to.c_str(), from.c_str(), nullptr);
        if (r != OSIP_SUCCESS) {
        LOG(ERROR) << "Build message ptzctl request failed, sipto: " << to << ", ret: " << r;
        return -1;
    }

    osip_message_set_body(msg, manscdp.str().c_str(), manscdp.str().length());
    osip_message_set_content_type(msg, "Application/MANSCDP+xml");
    int rid = eXosip_message_send_request(excontext, msg);
    if (rid < 1) {
        LOG(ERROR) << "send message ptzctl failed, ret: " << rid;
        return -1;
    }
}

}  // namespace GB28181