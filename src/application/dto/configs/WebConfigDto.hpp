#ifndef WebConfigDto_h
#define WebConfigDto_h

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class WebConfigDto : public oatpp::DTO {
    DTO_INIT(WebConfigDto, DTO)

    DTO_FIELD(String, host);
    DTO_FIELD(UInt16, port);
    DTO_FIELD(String, swaggerHost);
};

#include OATPP_CODEGEN_END(DTO)

#endif