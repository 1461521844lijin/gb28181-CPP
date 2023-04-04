#pragma once

#include "gb28181/request/base_request.h"

namespace GB28181 {

class PresetRequest : public MessageRequest {
public:
    typedef std::shared_ptr<PresetRequest> ptr;
    PresetRequest(Device::ptr device, std::string &channelId)
        : MessageRequest(device, REQ_MESSAGE_TYPE::DEVICE_QUIER_PRESET), m_channelId(channelId) {}

public:
    virtual const std::string make_manscdp_body() override;

private:
    std::string m_channelId = "";
};

}  // namespace GB28181