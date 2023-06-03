//
// Created by lijin on 2023/6/2.
//

#ifndef GB28181_CPP_KEEPALIVE_REQUEST_HPP
#define GB28181_CPP_KEEPALIVE_REQUEST_HPP

#include "gb28181/request/base_request.h"

namespace GB28181 {

class keepaliveRequest: public MessageRequest {

private:
    std::string m_gb_id;    // 国标id
    std::string m_ip;       // ip
    std::string m_port;     // 端口
public:
    typedef std::shared_ptr<keepaliveRequest> ptr;
    explicit keepaliveRequest(std::string gb_id,
                               std::string ip,
                               std::string port);
    ~keepaliveRequest() override = default;

    const std::string make_manscdp_body() override;

};

}  // namespace GB28181

#endif  // GB28181_CPP_KEEPALIVE_REQUEST_HPP
