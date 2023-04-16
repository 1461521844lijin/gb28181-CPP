#pragma once

#include "gb28181/event_handler/base_handler.h"
#include "utils/tinyxml2.h"

namespace GB28181
{


class PresetQuireHandler : public BaseHandler
{
public:
    int handle(SipEvent::ptr event, tinyxml2::XMLDocument& xml) override;
};


}