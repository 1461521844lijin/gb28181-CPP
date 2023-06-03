#pragma once

#include "gb28181/request/base_request.h"

namespace GB28181 {

class CatalogRequest : public MessageRequest {
public:
    typedef std::shared_ptr<CatalogRequest> ptr;
    explicit CatalogRequest(Device::ptr device) : MessageRequest(device) {}
    ~CatalogRequest() override = default;

public:
    const std::string make_manscdp_body() override;

    // virtual int HandleResponse(int statcode) override{
    //     return 0;
    // }
};
}  // namespace GB28181
