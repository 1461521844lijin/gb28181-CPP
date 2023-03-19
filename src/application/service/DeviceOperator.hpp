#pragma once

#include "application/dto/StatusDto.hpp"
#include "application/dto/PlayDto.hpp"

namespace Web
{
    
    oatpp::Object<StatusDto> do_taks(const oatpp::Object<PlayDto>& playItem);










} // namespace Web












