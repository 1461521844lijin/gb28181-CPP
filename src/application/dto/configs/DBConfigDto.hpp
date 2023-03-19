#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DBConfigDto : public oatpp::DTO {
    DTO_INIT(DBConfigDto, DTO)
    DTO_FIELD(String, dbConnectionString);
};

#include OATPP_CODEGEN_END(DTO)

