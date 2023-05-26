#pragma once
#include "application/service/DeviceOperator.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class DeviceController : public oatpp::web::server::api::ApiController {
public:
    DeviceController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<DeviceController>
    createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<DeviceController>(objectMapper);
    }

public:
    ENDPOINT_INFO(get_device_list) {
        info->summary = "获取设备列表";
        info->addTag("Device");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET", "/api/device/list", get_device_list) {
        return createDtoResponse(Status::CODE_200, OP::get_device_list());
    }
    ADD_CORS(get_device_list)

    ENDPOINT_INFO(home_position) {
        info->summary = "看守位控制";
        info->addTag("Device");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET",
             "/api/device/home_position/{deviceId}/{channelId}/{enabled}",
             home_position,
             PATH(String, deviceId),
             PATH(String, channelId),
             PATH(Int32, enabled),
             QUERY(Int32, presetIndex),
             QUERY(Int32, resetTime)) {
        return createDtoResponse(Status::CODE_200, OP::home_position(deviceId, channelId, enabled,
                                                                     presetIndex, resetTime));
    }
    ADD_CORS(home_position)


    ENDPOINT_INFO(device_guard){
        info->summary = "设备布防/撤防  命令可选值：SetGuard（布防），ResetGuard（撤防）";
        info->addTag("Device");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET",
             "/api/device/guard/{deviceId}/{guardCmdStr}",
             device_guard,
             PATH(String, deviceId),
             PATH(String, guardCmdStr)) {
        return createDtoResponse(Status::CODE_200, OP::device_guard(deviceId, guardCmdStr));
    }


};
