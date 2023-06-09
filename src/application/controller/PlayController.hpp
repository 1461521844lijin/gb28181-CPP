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


class PlayController : public oatpp::web::server::api::ApiController {
public:
    PlayController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<PlayController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<PlayController>(objectMapper);
    }

public:

    ENDPOINT_INFO(play_start) {
        info->summary = "国标设备点播";
        info->addTag("Play");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET", 
        "/api/play/start/{deviceId}/{channelId}", 
        play_start, 
        PATH(String, deviceId), 
        PATH(String, channelId) 
    ) {
        return createDtoResponse(Status::CODE_200, OP::play_start(deviceId, channelId));
    }
    ADD_CORS(play_start)

    ENDPOINT_INFO(play_stop) {
        info->summary = "国标设备停止点播";
        info->addTag("Play");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET", 
        "/api/play/stop/{deviceId}/{channelId}", 
        play_stop, 
        PATH(String, deviceId), 
        PATH(String, channelId) 
    ) {
        return createDtoResponse(Status::CODE_200, OP::play_stop(deviceId, channelId));
    }
    ADD_CORS(play_stop)

    ENDPOINT_INFO(play_stream_proxy) {
        info->summary = "代理拉流";
        info->addTag("Play");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
        info->addResponse<Object<DTO::GETWAY::StreamInfoDto>>(Status::CODE_200, "application/json");
    }
    ENDPOINT("POST", 
        "/api/play/stream_proxy", 
        play_stream_proxy, 
        BODY_DTO(Object<DTO::GETWAY::StreamPlayDto>, streamPlayDto)
    ) {
        return createDtoResponse(Status::CODE_200, OP::play_stream_proxy(streamPlayDto));
    }
    ADD_CORS(play_stream_proxy)
};
    


