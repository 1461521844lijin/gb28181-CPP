//
// Created by lijin on 2023/6/1.
//

#ifndef GB28181_CPP_PLATFORMOPERATOR_HPP
#define GB28181_CPP_PLATFORMOPERATOR_HPP
#include "application/dto/StatusDto.hpp"
#include "application/dto/api/PaltformInfoDto.hpp"
namespace OP {

oatpp::Object<StatusDto>
add_parent_platform(const oatpp::Object<DTO::GETWAY::PlatformInfoDto> &parentPlatformDto);

}  // namespace OP

#endif  // GB28181_CPP_PLATFORMOPERATOR_HPP
