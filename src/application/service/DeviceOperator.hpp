#pragma once

#include "application/dto/StatusDto.hpp"
#include "application/dto/api/DeviceInfoDto.hpp"

namespace OP {

oatpp::List<oatpp::Object<DTO::GETWAY::DeviceInfoDto>> get_device_list();

oatpp::Object<StatusDto> home_position(const std::string &deviceId,
                                       const std::string &channelId,
                                       const int         enabled,
                                       const int         presetIndex,
                                       const int         resetTime);


oatpp::Object<StatusDto> device_guard(const std::string &deviceId, const std::string &guardCmdStr);
                                       

}  // namespace OP