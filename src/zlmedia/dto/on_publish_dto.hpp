#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

// {
//    "mediaServerId" : "your_server_id",
//    "app" : "live",
//    "id" : "140186529001776",
//    "ip" : "10.0.17.132",
//    "params" : "token=1677193e-1244-49f2-8868-13b3fcc31b17",
//    "port" : 65284,
//    "schema" : "rtmp",
//    "stream" : "obs",
//    "vhost" : "__defaultVhost__"
// }

namespace DTO::ZLM {

class OnPublishDTO : public oatpp::DTO {
    DTO_INIT(OnPublishDTO, DTO)

    DTO_FIELD(String, mediaServerId);
    DTO_FIELD(String, app);
    DTO_FIELD(String, id);
    DTO_FIELD(String, ip);
    DTO_FIELD(String, params);
    DTO_FIELD(Int32, port);
    DTO_FIELD(String, schema);
    DTO_FIELD(String, stream);
    DTO_FIELD(String, vhost);
};

}  // namespace DTO::ZLM

#include OATPP_CODEGEN_END(DTO)
