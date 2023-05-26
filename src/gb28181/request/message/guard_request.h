#pragma once

#include "gb28181/request/base_request.h"

namespace GB28181 {

class GuardRequest : public MessageRequest {
public:
    typedef std::shared_ptr<GuardRequest> ptr;
    GuardRequest(Device::ptr device, const std::string &guardcmd)
        : MessageRequest(device, REQ_MESSAGE_TYPE::DEVICE_CONTROL_GUARD), m_guardcmd(guardcmd) {}

public:
    virtual const std::string make_manscdp_body() override;

    virtual int HandleResponse(int statcode, tinxml_doc_ptr xml = nullptr);

private:
    std::string m_guardcmd;
};

}  // namespace GB28181