//
// Created by lijin on 2023/6/2.
//

#include "keepalive_request.hpp"
#include "oatpp/core/macro/component.hpp"
#include "application/dto/configs/SipConfigDto.hpp"

namespace GB28181 {
keepaliveRequest::keepaliveRequest(std::string gb_id, std::string ip, std::string port) {
    m_gb_id = std::move(gb_id);
    m_ip = std::move(ip);
    m_port = std::move(port);
    Device::ptr device = std::make_shared<Device>(m_gb_id, m_ip, m_port);
    set_device(device);
}
const std::string keepaliveRequest::make_manscdp_body() {
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

    std::stringstream manscdp_body;
    manscdp_body << "<?xml version=\"1.0\" ?>\r\n";
    manscdp_body << "<Notify>\r\n";
    manscdp_body << "<CmdType>Keepalive</CmdType>\r\n";
    manscdp_body << "<SN>" << get_reqsn() << "</SN>\r\n";
    manscdp_body << "<DeviceID>" << *sipConfig->sipId << "</DeviceID>\r\n";
    manscdp_body << "<Status>OK</Status>\r\n";
    manscdp_body << "</Notify>\r\n";

    return manscdp_body.str();
}
}  // namespace GB28181