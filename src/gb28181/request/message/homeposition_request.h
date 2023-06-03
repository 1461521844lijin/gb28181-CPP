#pragma once
#include <utility>

#include "gb28181/request/base_request.h"
namespace GB28181 {

class HomePositionRequest : public MessageRequest {
public:
    typedef std::shared_ptr<HomePositionRequest> ptr;
    HomePositionRequest(Device::ptr device,
                        std::string channelId,
                        int         enable,
                        int         presetIndex,
                        int         resetTime)
        : MessageRequest(device),
          m_channelId(std::move(channelId)),
          m_enable(enable),
          m_presetIndex(presetIndex),
          m_resetTime(resetTime) {}

private:
    std::string m_channelId   = "";
    int         m_enable      = 0;
    int         m_presetIndex = 0;
    int         m_resetTime   = 0;

public:
    virtual const std::string make_manscdp_body() override;
};

}  // namespace GB28181
