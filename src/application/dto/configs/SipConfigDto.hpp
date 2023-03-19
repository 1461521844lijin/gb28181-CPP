#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

//
//         "sipId": "34020000002000000001",
//         "sipDimain": "3402000000",
//         "sipPassword": "admin123",
//         "sipHost": "192.168.161.149",
//         "sipPort": 5060,
//         "sipPa": "GBCPP"
//

class SipConfigDto : public oatpp::DTO {
    DTO_INIT(SipConfigDto, DTO)

    DTO_FIELD(String, sipId);
    DTO_FIELD(String, sipDimain);
    DTO_FIELD(String, sipPassword);
    DTO_FIELD(String, sipHost);
    DTO_FIELD(Int32, sipPort);
    DTO_FIELD(String, sipPa);
    DTO_FIELD(String, sipNonce);
};

#include OATPP_CODEGEN_END(DTO)
