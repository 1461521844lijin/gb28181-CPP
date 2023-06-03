#pragma once

#include <utility>

#include "gb28181/request/base_request.h"

namespace GB28181 {

class PresetCtlRequest : public MessageRequest {
public:
    typedef std::shared_ptr<PresetCtlRequest> ptr;
    PresetCtlRequest(Device::ptr device,
                     std::string channelId,
                     int         byte4,
                     int         byte5,
                     int         byte6,
                     int         byte7)
        : MessageRequest(device),
          m_byte4(byte4),
          m_byte5(byte5),
          m_byte6(byte6),
          m_byte7(byte7),
          m_channelId(std::move(channelId)) {}

    const std::string make_manscdp_body() override;

private:
    int m_byte4 = 0;
    int m_byte5 = 0;
    int m_byte6 = 0;
    int m_byte7 = 0;
    std::string m_channelId = "";
};

}  // namespace GB28181