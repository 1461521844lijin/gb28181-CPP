#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace DTO::ZLM {

class openRtpServerRes : public oatpp::DTO {
    DTO_INIT(openRtpServerRes, DTO)

    DTO_FIELD(Int32, code);
    DTO_FIELD(Int32, port);
    DTO_FIELD(String, msg);
};
}

  // namespace DTO::ZLM