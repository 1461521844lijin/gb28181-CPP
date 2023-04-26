#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"


#include "zlmedia/dto/on_server_keepalive_dto.hpp"
#include "zlmedia/dto/on_stream_changed_dto.hpp"
#include "zlmedia/dto/on_publish_dto.hpp"

#include "web_hook_operator.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace ZLM
{



class ZlmWebHookController : public oatpp::web::server::api::ApiController {
public:
    ZlmWebHookController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<ZlmWebHookController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<ZlmWebHookController>(objectMapper);
    }

public:

    ENDPOINT_INFO(on_server_keepalive) {
        info->summary = "zlm服务器心跳";
        info->addTag("zlm_web_hook");
        info->addConsumes<Object<DTO::ZLM::OnServerKeepaliveDto>>("application/json");
        info->addResponse<Object<DTO::ZLM::ResponseDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST", 
        "/index/hook/on_server_keepalive", 
        on_server_keepalive, 
        BODY_DTO(Object<DTO::ZLM::OnServerKeepaliveDto>, onServerKeepaliveDto)
    ) {
        return createDtoResponse(Status::CODE_200, on_server_keepalive_api(onServerKeepaliveDto));
    }


    ENDPOINT_INFO(on_stream_changed) {
        info->summary = "zlm流状态变更";
        info->addTag("zlm_web_hook");
        info->addConsumes<Object<DTO::ZLM::OnStreamChangedDTO>>("application/json");
        info->addResponse<Object<DTO::ZLM::ResponseDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST", 
        "/index/hook/on_stream_changed", 
        on_stream_changed, 
        BODY_DTO(Object<DTO::ZLM::OnStreamChangedDTO>, onStreamChangedDTO)
    ) {
        return createDtoResponse(Status::CODE_200, on_stream_changed_api(onStreamChangedDTO));
    }

    ENDPOINT_INFO(on_stream_none_reader) {
        info->summary = "zlm无流观看事件";
        info->addTag("zlm_web_hook");
        info->addConsumes<Object<DTO::ZLM::OnStreamChangedDTO>>("application/json");
        info->addResponse<Object<DTO::ZLM::ResponseDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST", 
        "/index/hook/on_stream_none_reader", 
        on_stream_none_reader, 
        BODY_DTO(Object<DTO::ZLM::OnStreamChangedDTO>, onStreamChangedDTO)
    ) {
        return createDtoResponse(Status::CODE_200, on_stream_none_reader_api(onStreamChangedDTO));
    }

    ENDPOINT_INFO(on_publish) {
        info->summary = "rtsp/rtmp/rtp推流鉴权事件";
        info->addTag("zlm_web_hook");
        info->addResponse<Object<DTO::ZLM::ResponseDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST",
        "/index/hook/on_publish",
        on_publish,
        BODY_DTO(Object<DTO::ZLM::OnPublishDTO>, onPublish)
    ){
        return createDtoResponse(Status::CODE_200, on_publish_api(onPublish));
    }

    ENDPOINT_INFO(on_play) {
        info->summary = "播放鉴权事件";
        info->addTag("zlm_web_hook");
        info->addResponse<Object<DTO::ZLM::ResponseDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST",
        "/index/hook/on_play",
        on_play,
        BODY_DTO(Object<DTO::ZLM::OnPublishDTO>, onPublish)
    ){
        return createDtoResponse(Status::CODE_200, on_play_api(onPublish));
    }







};
    
} // namespace ZLM







