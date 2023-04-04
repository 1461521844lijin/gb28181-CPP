#pragma once

#include "application/dto/StatusDto.hpp"
#include "application/dto/PlayDto.hpp"

namespace Web
{
    
    oatpp::Object<StatusDto> do_taks(const oatpp::Object<PlayDto>& playItem);

    oatpp::Object<StatusDto> ptz_ctl(const oatpp::Object<PtzDto>& ptzItem);

    oatpp::Object<StatusDto> preset_quire(const oatpp::Object<PlayDto>& playItem);

    oatpp::Object<StatusDto> preset_control(const oatpp::Object<PlayDto>& playItem);





} // namespace Web












