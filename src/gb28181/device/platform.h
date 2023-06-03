#pragma once
#include "Poller/Timer.h"
#include "gb28181/request/call/register_request.h"
#include "gb28181/request/message/keepalive_request.hpp"
#include "utils/Singleton.h"
#include <memory>
#include <string>
#include <utility>

#include "device.h"

namespace GB28181 {

class Platform : public Device {
private:
    std::string m_platform_gb_domain;   // 平台域名
    int         m_expires      = 3600;  // 平台注册过期时间
    int         m_keep_timeout = 60;    // 平台心跳间隔时间
    std::string m_sip_password;         // sip密码
    bool        m_allow_ptz;            // 是否允许云台控制

public:
    typedef std::shared_ptr<Platform> ptr;
    Platform() = delete;
    explicit Platform(std::string sip_password,
                      std::string platform_gb_id,
                      std::string platform_gb_domain,
                      std::string platform_ip,
                      std::string platform_port,
                      std::string platform_name,
                      bool        allow_ptz,
                      int         expires      = 3600,
                      int         keep_timeout = 60);

private:

    int                  rid;          // exosip注册id
    bool                 m_registerd;  // 是否注册成功
    bool                 m_status;     // 平台在线状态
    RegisterRequest::ptr m_register_request;
    keepaliveRequest::ptr m_keepalive_request;

    toolkit::Timer::Ptr m_keepalive_timer = nullptr;  // 心跳定时器
    toolkit::Timer::Ptr m_register_timer = nullptr;  // 注册定时器

public:
    bool register_platform();

    bool unregister_platform();

    void start_keepalive_timer();

    void start_register_timer();

public:
    int  get_rid() const;
    void set_rid(int rid);

    std::string get_platform_gb_domain() const;
    void        set_platform_gb_domain(const std::string &platform_gb_domain);

    int  get_expires() const;
    void set_expires(int expires);

    int  get_keep_timeout() const;
    void set_keep_timeout(int keep_timeout);

    std::string get_sip_password() const;
    void        set_sip_password(const std::string &sip_password);

    bool get_allow_ptz() const;
    void set_allow_ptz(bool allow_ptz);

    bool get_registerd() const;
    void set_registerd(bool registerd);

    bool get_status() const;
    void set_status(bool status);
};

}  // namespace GB28181