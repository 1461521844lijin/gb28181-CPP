#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class PlayDto : public oatpp::DTO {
    DTO_INIT(PlayDto, DTO)

    DTO_FIELD(String, deviceId);
    DTO_FIELD(String, op);
};

#include OATPP_CODEGEN_END(DTO)