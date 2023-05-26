#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include "application/dto/StatusDto.hpp"
#include "application/dto/media_server/PlayDto.hpp"

#include "application/service/PlayOperator.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)


class PlatformController : public oatpp::web::server::api::ApiController {
public:
    PlatformController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<PlatformController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<PlatformController>(objectMapper);
    }

public:

    ENDPOINT_INFO(get_platform_config) {
        info->summary = "获取平台国标配置";
        info->addTag("Platform");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET", 
        "/api/platform/config", 
        get_platform_config
    ) {
        return createDtoResponse(Status::CODE_200, StatusDto::createShared());
    }


















};