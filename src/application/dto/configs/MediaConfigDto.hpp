#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

// "zlmAddr": "192.168.161.149",
// "zlmPort": 80,
// "zlmSecret": "035c73f7-bb6b-4889-a715-d9eb2d1925cc"

class MediaConfigDto : public oatpp::DTO{
    DTO_INIT(MediaConfigDto, DTO)

    DTO_FIELD(String, zlmAddr);
    DTO_FIELD(Int32, zlmPort);
    DTO_FIELD(String, zlmSecret);
    DTO_FIELD(Int32, zlmRtpPort);
};

#include OATPP_CODEGEN_END(DTO)