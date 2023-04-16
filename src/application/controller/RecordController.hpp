#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"


#include "application/dto/StatusDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class RecordController : public oatpp::web::server::api::ApiController {
public:
    RecordController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<RecordController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<RecordController>(objectMapper);
    }

public:

    ENDPOINT_INFO(getRecordList) {
        info->summary = "获取录制列表";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/getMp4RecordFile", 
        getRecordList,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream"),
        QUERY(String, vhost, "vhost"),
        QUERY(String, period, "period")
        ) {
        return createDtoResponse(Status::CODE_200, StatusDto::createShared());
    } 

    ENDPOINT_INFO(startRecord) {
        info->summary = "开始录制";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/startRecord", 
        startRecord,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream"),
        QUERY(String, vhost, "vhost")
        ) {
        return createDtoResponse(Status::CODE_200, StatusDto::createShared());
    }

    ENDPOINT_INFO(stopRecord) {
        info->summary = "停止录制";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/stopRecord", 
        stopRecord,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream"),
        QUERY(String, vhost, "vhost")
        ) {
        return createDtoResponse(Status::CODE_200, StatusDto::createShared());
    }

    ENDPOINT_INFO(isRecording) {
        info->summary = "获取流录制状态";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/isRecording", 
        isRecording,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream"),
        QUERY(String, vhost, "vhost")
        ) {
        return createDtoResponse(Status::CODE_200, StatusDto::createShared());
    }

    ENDPOINT_INFO(getSnap) {
        info->summary = "获取截图或生成实时截图并返回";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/getSnap", 
        getSnap,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream"),
        QUERY(String, vhost, "vhost"),
        QUERY(String, time, "time")
        ) {
        return createDtoResponse(Status::CODE_200, StatusDto::createShared());
    }



};