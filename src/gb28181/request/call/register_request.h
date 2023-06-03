#pragma once

#include <utility>

#include "gb28181/request/base_request.h"
#include "zlmedia/zlmedia_server/zlm_server.hpp"

namespace GB28181 {

class RegisterRequest : public BaseRequest, public std::enable_shared_from_this<BaseRequest> {
private:
    std::string m_gb_id;    // 国标id
    std::string m_ip;       // ip
    std::string m_port;     // 端口
    std::string m_domain;   // 域名
    std::string m_password;
    int         m_expires;  // 注册过期时间

public:
    typedef std::shared_ptr<RegisterRequest> ptr;
    explicit RegisterRequest(std::string gb_id,
                             std::string ip,
                             std::string port,
                             std::string domain,
                             std::string password,
                             int         expires);
    ~RegisterRequest() override = default;

    /**
     * @brief 发送注册请求
     * @param isRegister 注册/注销
     * @return 0:成功，非0:失败
     */
    int send_register(bool isRegister);
};

}  // namespace GB28181