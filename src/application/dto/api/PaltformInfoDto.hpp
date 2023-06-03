//
// Created by lijin on 2023/6/1.
//

#ifndef GB28181_CPP_PALTFORMINFODTO_HPP
#define GB28181_CPP_PALTFORMINFODTO_HPP

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace DTO::GETWAY {

class PlatformInfoDto : public oatpp::DTO {
    DTO_INIT(PlatformInfoDto, DTO)
    DTO_FIELD(String, platform_id);
    DTO_FIELD(String, platform_name);
    DTO_FIELD(String, platform_domain);
    DTO_FIELD(String, platform_ip);
    DTO_FIELD(String, platform_port);
    DTO_FIELD(String, platform_password);
};
}  // namespace DTO::GETWAY

#endif  // GB28181_CPP_PALTFORMINFODTO_HPP
