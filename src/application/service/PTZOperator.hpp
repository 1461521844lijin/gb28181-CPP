#pragma once
#include "application/dto/StatusDto.hpp"
#include "application/dto/api/PresetInfoDto.hpp"

namespace OP {

oatpp::Object<StatusDto> ptz_ctl(const std::string &deviceId,
                                 const std::string &channelId,
                                 const std::string &command,
                                 const int          speed);

oatpp::Object<StatusDto> preset_operate(const std::string &deviceId,
                                        const std::string &channelId,
                                        const std::string &command,
                                        const int          presetIndex);

oatpp::List<oatpp::Object<DTO::GETWAY::PresetInfoDto>> preset_query(const std::string &deviceId, const std::string &channelId);

oatpp::Object<StatusDto> front_end_command(const std::string &deviceId,
                                           const std::string &channelId,
                                           const int          cmdCode,
                                           const int          parameter1,
                                           const int          parameter2,
                                           const int          combindCode2);

}  // namespace OP
