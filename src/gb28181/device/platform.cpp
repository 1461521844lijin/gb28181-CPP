#include "platform.h"
#include "Util/logger.h"
#include "gb28181/manscdp/defs/defs.h"

namespace GB28181 {

Platform::Platform(std::string sip_password,
                   std::string platform_gb_id,
                   std::string platform_gb_domain,
                   std::string platform_ip,
                   std::string platform_port,
                   std::string platform_name,
                   bool        allow_ptz,
                   int         expires,
                   int         keep_timeout)
    : Device(platform_gb_id, platform_ip, platform_port),
      m_platform_gb_domain(std::move(platform_gb_domain)),
      m_expires(expires),
      m_keep_timeout(keep_timeout),
      m_sip_password(std::move(sip_password)),
      m_allow_ptz(allow_ptz) {
    setName(platform_name);
    m_register_request = std::make_shared<RegisterRequest>(
        getDeviceId(), getIp(), getPort(), m_platform_gb_domain, m_sip_password, m_expires);
    m_keepalive_request = std::make_shared<keepaliveRequest>(getDeviceId(), getIp(), getPort());
}

int Platform::get_rid() const {
    return rid;
}

void Platform::set_rid(int rid) {
    std::lock_guard<std::mutex> lock(m_mutex);
    Platform::rid = rid;
}

std::string Platform::get_platform_gb_domain() const {
    return m_platform_gb_domain;
}

void Platform::set_platform_gb_domain(const std::string &platform_gb_domain) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_platform_gb_domain = platform_gb_domain;
}

int Platform::get_expires() const {
    return m_expires;
}

void Platform::set_expires(int expires) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_expires = expires;
}

int Platform::get_keep_timeout() const {
    return m_keep_timeout;
}

void Platform::set_keep_timeout(int keep_timeout) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_keep_timeout = keep_timeout;
}

std::string Platform::get_sip_password() const {
    return m_sip_password;
}

void Platform::set_sip_password(const std::string &sip_password) {
    m_sip_password = sip_password;
}

bool Platform::get_allow_ptz() const {
    return m_allow_ptz;
}

void Platform::set_allow_ptz(bool allow_ptz) {
    m_allow_ptz = allow_ptz;
}

bool Platform::get_registerd() const {
    return m_registerd;
}

void Platform::set_registerd(bool registerd) {
    m_registerd = registerd;
}

bool Platform::get_status() const {
    return m_status;
}

void Platform::set_status(bool status) {
    m_status = status;
}

bool Platform::register_platform() {
    auto rid = m_register_request->send_register(true);
    if (rid > 0) {
        set_rid(rid);
        return true;
    } else {
        ErrorL << "register platform failed";
        return false;
    }
}

bool Platform::unregister_platform() {
    auto rid = m_register_request->send_register(false);
    if (rid > 0) {
        m_register_timer.reset();  // 注销成功后，取消注册定时器
        m_keepalive_timer.reset();
        return true;
    } else {
        ErrorL << "unregister platform failed";
        return false;
    }
}

void Platform::start_keepalive_timer() {
    if (!m_keepalive_timer) {
        m_keepalive_timer.reset(
            new toolkit::Timer(
                (float)get_keep_timeout(),
                   [this]() {
                           if (getStatus()) {
                               m_keepalive_request->send_message();
                               return true;
                           } else {
                               return false;
                           }
                       },
               nullptr));

        m_keepalive_request->set_response_callback([this](int x, const tinxml_doc_ptr& xml){
            DebugL << "keepalive response :" << x;
            // todo 定时检测逻辑，当超过一定时间未收到心跳回复时，认为平台离线
        });

    }
}

void Platform::start_register_timer() {
    if (!m_register_timer) {
        m_register_timer.reset(
            new toolkit::Timer(
                (float)get_expires(),
                    [this]() {
                              if (getStatus()) {
                                  m_register_request->send_register(true);
                                  return true;
                              } else {
                                  return false;
                              }
                        },
                    nullptr));
    }
}

}  // namespace GB28181