#pragma once

#include "gb28181/event_handler/base_handler.h"
#include "utils/tinyxml2.h"
namespace GB28181
{
    


class KeepaliveHandler : public BaseHandler
{
private:
    /* data */
public:
    KeepaliveHandler(/* args */) = default;
    ~KeepaliveHandler() = default;

    int handle(SipEvent::ptr event, tinyxml2::XMLDocument& xml) override;
};


} // namespace name
