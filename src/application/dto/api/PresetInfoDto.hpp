#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "application/dto/StatusDto.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)


namespace DTO::GETWAY 
{


    class  PresetInfoDto : public oatpp::DTO 
    {
        DTO_INIT(PresetInfoDto, DTO)

        DTO_FIELD(String, preset_id);
        DTO_FIELD(String, preset_name);
    };




    
} // namespace DTO:

#include OATPP_CODEGEN_END(DTO)


