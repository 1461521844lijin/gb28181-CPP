#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class PlayDto : public oatpp::DTO {
    DTO_INIT(PlayDto, DTO)

    DTO_FIELD(String, deviceId);
    DTO_FIELD(String, op);
};


class PtzDto: public PlayDto {
    DTO_INIT(PtzDto, PlayDto)


    //  * @param upDown        
    //  * @param inOut        
    //  * @param moveSpeed     
    //  * @param zoomSpeed
    DTO_FIELD(Int32, leftRight);
    DTO_FIELD(Int32, upDown);
    DTO_FIELD(Int32, inOut);
    DTO_FIELD(Int32, moveSpeed);
    DTO_FIELD(Int32, zoomSpeed);
};

#include OATPP_CODEGEN_END(DTO)