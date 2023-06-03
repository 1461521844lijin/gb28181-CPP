#include "register_request.h"
#include "Util/logger.h"
#include "application/dto/configs/MediaConfigDto.hpp"
#include "application/dto/configs/SipConfigDto.hpp"
#include "gb28181/request/requested_pool.h"
#include "gb28181/sip_server.h"
#include "oatpp/core/macro/component.hpp"
#include <iostream>
namespace GB28181 {

RegisterRequest::RegisterRequest(std::string gb_id,
                                 std::string ip,
                                 std::string port,
                                 std::string domain,
                                 std::string password,
                                 int         expires) {
    m_gb_id    = std::move(gb_id);
    m_ip       = std::move(ip);
    m_port     = std::move(port);
    m_domain   = std::move(domain);
    m_password = std::move(password);
    m_expires  = expires;
}

int RegisterRequest::send_register(bool isRegister) {
    auto sip_context = g_SipServer ::GetInstance()->GetExosipContext();
    if (nullptr == sip_context) {
        ErrorL << "sip_context is null";
        return -1;
    }
    int expires;
    if (!isRegister) {
        m_expires = 0;
    }
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);
    osip_message_t *reg  = nullptr;
    std::string     from = "sip:" + sipConfig->sipId + "@" + sipConfig->sipHost + ":" +
                       std::to_string(sipConfig->sipPort);
    std::string proxy = "sip:" + m_gb_id + "@" + m_ip + ":" + m_port;

    DebugL << "from:" << from << std::endl;
    DebugL << "proxy:" << proxy << std::endl;

    exosip_guard guard(sip_context);

    int rid = eXosip_register_build_initial_register(sip_context, from.c_str(), proxy.c_str(),
                                                     nullptr, m_expires, &reg);
    if (rid <= 0) {
        ErrorL << "eXosip_register_build_initial_register error:" << rid;
        return -1;
    }

    eXosip_add_authentication_info(sip_context, m_gb_id.c_str(), m_ip.c_str(), m_password.c_str(),
                                   "MD5", nullptr);

    int r = eXosip_register_send_register(sip_context, rid, reg);
    if (r != 0) {
        ErrorL << "eXosip_register_send_register error:" << r;
        return -1;
    }





    return rid;
}
}  // namespace GB28181