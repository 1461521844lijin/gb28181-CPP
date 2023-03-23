#pragma once

#include "gb28181/request/base_request.h"

namespace GB28181
{

class CatalogRequest : public MessageRequest
{
public:
    typedef std::shared_ptr<CatalogRequest> ptr;
    CatalogRequest(Device::ptr device, const std::string& reqsn):MessageRequest(device, reqsn, REQ_MESSAGE_TYPE::QUIRY_CATALOG){}
    ~CatalogRequest() = default;
public:

    virtual const std::string& make_manscdp_body() override;


    virtual int HandleResponse(int statcode) override{
        return 0;
    }


};    
} // namespace GB28181














