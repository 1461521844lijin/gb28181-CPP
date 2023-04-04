#pragma once
#include "application/dto/StatusDto.hpp"

namespace OP
{



    oatpp::Object<StatusDto> ptz_ctl(const std::string& deviceId, const std::string& channelId, const std::string& command, const int speed);




    
} // namespace OPERATOR


