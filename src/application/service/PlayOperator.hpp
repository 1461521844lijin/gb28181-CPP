#pragma once
#include "application/dto/StatusDto.hpp"
#include "application/dto/api/StreamInfoDto.hpp"

namespace OP {

oatpp::Object<StatusDto> play_start(const std::string &deviceId, const std::string &channelId);

oatpp::Object<StatusDto> play_stop(const std::string &deviceId, const std::string &channelId);

oatpp::Object<DTO::GETWAY::StreamInfoDto> play_stream_proxy(const oatpp::Object<DTO::GETWAY::StreamPlayDto>& streamPlayDto);

}  // namespace OP