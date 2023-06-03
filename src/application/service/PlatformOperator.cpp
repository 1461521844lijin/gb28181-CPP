//
// Created by lijin on 2023/6/1.
//

#include "PlatformOperator.hpp"
#include "gb28181/device/platform.h"
#include "gb28181/device/platformManger.hpp"

namespace OP {

oatpp::Object<StatusDto>
add_parent_platform(const oatpp::Object<DTO::GETWAY::PlatformInfoDto> &parentPlatformDto) {
    //    GB28181::Platform::platform_info platform_info;
    std::string            platform_name   = parentPlatformDto->platform_name;
    std::string            platform_gb_id  = parentPlatformDto->platform_id;
    std::string            platform_domain = parentPlatformDto->platform_domain;
    std::string            platform_ip     = parentPlatformDto->platform_ip;
    std::string            platform_port   = parentPlatformDto->platform_port;
    std::string            sip_password    = parentPlatformDto->platform_password;
    GB28181::Platform::ptr platform =
        std::make_shared<GB28181::Platform>(sip_password, platform_gb_id, platform_domain,
                                            platform_ip, platform_port, platform_name, true, 3600, 30);
    platform->register_platform();
    GB28181::g_platformMgr::GetInstance()->addPlatform(platform);

    auto status  = StatusDto::createShared();
    status->code = 200;
    status->msg  = "success";
    return status;
}

}  // namespace OP