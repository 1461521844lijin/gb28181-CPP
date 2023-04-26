#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "application/dto/StatusDto.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)


namespace DTO::GETWAY 
{


    class  StreamInfoDto : public StatusDto
    {
        DTO_INIT(StreamInfoDto, StatusDto)

        DTO_FIELD_INFO(playUrl) {
            info->description = "返回的webrtc拉流地址";
        };
        DTO_FIELD(String, playUrl);

    };


    class StreamPlayDto: public oatpp::DTO{
        DTO_INIT(StreamPlayDto, DTO)

        DTO_FIELD_INFO(streamCode) {
            info->description = "流地址唯一标识";
            info->required = true;
        };
        DTO_FIELD(String, streamCode);
        
        DTO_FIELD_INFO(streamUrl) {
            info->description = "拉流地址";
        };
        DTO_FIELD(String, streamUrl);
    };


    class ProxyData: public oatpp::DTO{
        DTO_INIT(ProxyData, DTO)

        DTO_FIELD(String, key) = "";
    };

    class StreamProxyDto: public StatusDto{
        DTO_INIT(StreamProxyDto, StatusDto)
        DTO_FIELD(oatpp::Object<ProxyData>, data);      
    };
    

    
} // namespace DTO:

#include OATPP_CODEGEN_END(DTO)


