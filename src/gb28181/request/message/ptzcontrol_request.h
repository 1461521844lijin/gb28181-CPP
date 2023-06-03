#pragma once

#include <utility>

#include "Util/logger.h"
#include "gb28181/request/base_request.h"

namespace GB28181 {

class PtzControlRequest : public MessageRequest {
public:
    typedef std::shared_ptr<PtzControlRequest> ptr;
    PtzControlRequest(Device::ptr device,
                      std::string channelId,
                      int         leftRight,
                      int         upDown,
                      int         inOut,
                      int         moveSpeed,
                      int         zoomSpeed)
        : MessageRequest(device),
          m_leftRight(leftRight),
          m_upDown(upDown),
          m_inOut(inOut),
          m_moveSpeed(moveSpeed),
          m_zoomSpeed(zoomSpeed),
          m_channelId(std::move(channelId)) {}
    ~PtzControlRequest() = default;

public:
    virtual const std::string make_manscdp_body() override;

    virtual int HandleResponse(int statcode, tinxml_doc_ptr xml = nullptr) override {
        m_leftRight = 0;
        m_upDown    = 0;
        m_inOut     = 0;
        m_moveSpeed = 0;
        m_zoomSpeed = 0;

        // 收到相机回复后，立即停止云台转动
        InfoL << "PtzControlRequest HandleResponse statuscode = "<<statcode;
        // send_message(false);
        return 0;
    }

private:
    int m_leftRight = 0;
    int m_upDown    = 0;
    int m_inOut     = 0;
    int m_moveSpeed = 0;
    int m_zoomSpeed = 0;

    std::string m_channelId;
};

}  // namespace GB28181
