#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include "application/dto/StatusDto.hpp"
#include "application/dto/media_server/PlayDto.hpp"

#include "application/service/PTZOperator.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class PTZController : public oatpp::web::server::api::ApiController {
public:
    PTZController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<PTZController>
    createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<PTZController>(objectMapper);
    }

public:
    ENDPOINT_INFO(device_ptz_ctl) {
        info->summary = "国标设备ptz控制相关操作";
        info->description = "command控制指令,允许值: left, right, up, down, upleft, upright, "
                            "downleft, downright, zoomin, zoomout, stop";
        info->addTag("PTZ");
        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET",
             "/api/ptz/control/{deviceId}/{channelId}",
             device_ptz_ctl,
             PATH(String, deviceId),
             PATH(String, channelId),
             QUERY(String, command),
             QUERY(Int32, speed)) {
        return createDtoResponse(Status::CODE_200,
                                 OP::ptz_ctl(deviceId, channelId, command, speed));
    }
    ADD_CORS(device_ptz_ctl)

    ENDPOINT_INFO(device_ptz_preset_operate) {
        info->summary = "国标设备ptz预置位相关操作";
        info->addTag("PTZ");
        info->description = "command控制指令,允许值: set, goto, del";
        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET",
             "/api/ptz/preset/operate/{deviceId}/{channelId}",
             device_ptz_preset_operate,
             PATH(String, deviceId),
             PATH(String, channelId),
             QUERY(String, command),
             QUERY(Int32, presetIndex)) {
        return createDtoResponse(Status::CODE_200,
                                 OP::preset_operate(deviceId, channelId, command, presetIndex));
    }
    ADD_CORS(device_ptz_preset_operate)

    ENDPOINT_INFO(device_ptz_preset_query) {
        info->summary = "国标设备ptz预置位查询";
        info->addTag("PTZ");
        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET",
             "/api/ptz/preset/query/{deviceId}/{channelId}",
             device_ptz_preset_query,
             PATH(String, deviceId),
             PATH(String, channelId)) {
        return createDtoResponse(Status::CODE_200, OP::preset_query(deviceId, channelId));
    }
    ADD_CORS(device_ptz_preset_query)

    ENDPOINT_INFO(front_end_command) {
        info->summary = "通用前端控制命令";
        info->addTag("PTZ");
        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET",
             "/api/ptz/front_end_command/{deviceId}/{channelId}",
             front_end_command,
             PATH(String, deviceId),
             PATH(String, channelId),
             QUERY(Int32, cmdCode),
             QUERY(Int32, parameter1),
             QUERY(Int32, parameter2),
             QUERY(Int32, combindCode2)) {
        return createDtoResponse(Status::CODE_200,
                                 OP::front_end_command(deviceId, channelId, cmdCode, parameter1,
                                                       parameter2, combindCode2));
    }
    ADD_CORS(front_end_command)
};