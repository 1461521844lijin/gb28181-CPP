#pragma once
#include "application/dto/StatusDto.hpp"

namespace OP
{

    oatpp::Object<StatusDto> play_start(const std::string& deviceId, const std::string& channelId);

    oatpp::Object<StatusDto> play_stop(const std::string& deviceId, const std::string& channelId);

}