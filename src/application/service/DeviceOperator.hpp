#pragma once

#include "application/dto/StatusDto.hpp"
#include "application/dto/PlayDto.hpp"

namespace Web
{
    
    oatpp::Object<StatusDto> do_taks(const oatpp::Object<PlayDto>& playItem);

    oatpp::Object<StatusDto> ptz_ctl(const oatpp::Object<PtzDto>& playItem);










} // namespace Web












