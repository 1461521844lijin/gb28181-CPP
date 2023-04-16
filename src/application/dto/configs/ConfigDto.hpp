
#ifndef ConfigDto_hpp
#define ConfigDto_hpp

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "DBConfigDto.hpp"
#include "LogConfigDto.hpp"
#include "MediaConfigDto.hpp"
#include "SipConfigDto.hpp"
#include "WebConfigDto.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class ConfigDto : public oatpp::DTO {
    DTO_INIT(ConfigDto, DTO)

    DTO_FIELD(oatpp::Object<WebConfigDto>, web);
    DTO_FIELD(oatpp::Object<DBConfigDto>, database);
    DTO_FIELD(oatpp::Object<LogConfigDto>, log);
    DTO_FIELD(oatpp::Object<MediaConfigDto>, media);
    DTO_FIELD(oatpp::Object<SipConfigDto>, sip);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ConfigDto_hpp */