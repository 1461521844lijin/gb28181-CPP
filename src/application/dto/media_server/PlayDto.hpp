#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class PlayDto : public oatpp::DTO {
    DTO_INIT(PlayDto, DTO)

    DTO_FIELD(String, deviceId) = "";
    DTO_FIELD(String, channelId) = "";
    DTO_FIELD(String, op) = "";
    DTO_FIELD(Int32, presetId) = 0;
};


class PtzDto: public PlayDto {
    DTO_INIT(PtzDto, PlayDto)

    DTO_FIELD(Int32, leftRight) = 0;
    DTO_FIELD(Int32, upDown) = 0;
    DTO_FIELD(Int32, inOut) = 0;
    DTO_FIELD(Int32, moveSpeed) = 0;
    DTO_FIELD(Int32, zoomSpeed) = 0;

};

#include OATPP_CODEGEN_END(DTO)