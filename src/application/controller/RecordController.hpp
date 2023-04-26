#pragma once
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"


#include "application/dto/StatusDto.hpp"
#include "application/service/RecordOperator.h"

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
        QUERY(String, period, "period")
        ) {
        return createDtoResponse(Status::CODE_200, OP::getMp4RecordFile(app, stream, period));
    }
    ADD_CORS(getRecordList) 

    ENDPOINT_INFO(startRecord) {
        info->summary = "开始录制mp4";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/startRecord", 
        startRecord,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream"),
        QUERY(Int32, maxSecond, "maxSecond")
        ) {
        return createDtoResponse(Status::CODE_200, OP::startRecord(app, stream, maxSecond));
    }
    ADD_CORS(startRecord)

    ENDPOINT_INFO(stopRecord) {
        info->summary = "停止录制";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/stopRecord", 
        stopRecord,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream")
        ) {
        return createDtoResponse(Status::CODE_200, OP::stopRecord(app, stream));
    }
    ADD_CORS(stopRecord)

    ENDPOINT_INFO(isRecording) {
        info->summary = "获取流录制状态";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/isRecording", 
        isRecording,
        QUERY(String, app, "app"),
        QUERY(String, stream, "stream")
        ) {
        return createDtoResponse(Status::CODE_200, OP::getRecordStatus(app, stream));
    }
    ADD_CORS(isRecording)

    ENDPOINT_INFO(getSnap) {
        info->summary = "获取截图或生成实时截图并返回";
        info->addTag("Record");
    }
    ENDPOINT("POST",
        "/api/record/getSnap", 
        getSnap,
        BODY_DTO(Object<DTO::GETWAY::StreamPlayDto>, streamPlayDto)
        ) {
        auto response = createResponse(Status::CODE_200, OP::getSnapShot(streamPlayDto));
        response->putHeader("Content-Type", "image/jpeg");
        return response;
    }
    ADD_CORS(getSnap)

    ENDPOINT_INFO(setRecordSpeed) {
        info->summary = "设置录像流播放速度";
        info->addTag("Record");
    }
    ENDPOINT("GET",
        "/api/record/setRecordSpeed", 
        setRecordSpeed,
        QUERY(String, path, "path"),
        QUERY(Float32, speed, "speed")
        ) {
        return createDtoResponse(Status::CODE_200, OP::setRecordSpeed(path, speed));
    }
    ADD_CORS(setRecordSpeed)

};