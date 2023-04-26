#include "RecordOperator.h"

#include "Util/logger.h"
#include "gb28181/device/base_stream.h"
#include "zlmedia/zlmedia_server/zlm_manager.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

namespace OP {

oatpp::Object<DTO::GETWAY::RecordResDto> getMp4RecordFile(const std::string &app,
                                                          const std::string &streamid,
                                                          const std::string &period) {
    GB28181::BaseStream::ptr stream = GB28181::g_StreamMgr::GetInstance()->getStream(streamid);
    if (stream) {
        auto zlm_server = stream->getMediaServer();
        if (zlm_server) {
            auto res = zlm_server->getMp4RecordFile(app, streamid, period);
            DebugL << res;
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto result =
                json_Mapper->readFromString<oatpp::Object<DTO::GETWAY::RecordResDto>>(res);
            return result;
        }
    } else {
        auto result  = DTO::GETWAY::RecordResDto::createShared();
        result->code = -1;
        result->msg  = "stream not exist";
        return result;
    }
}

oatpp::Object<DTO::GETWAY::RecordResDto> startRecord(const std::string &app,
                                                     const std::string &streamid,
                                                     const int          max_second) {
    GB28181::BaseStream::ptr stream = GB28181::g_StreamMgr::GetInstance()->getStream(streamid);
    if (stream) {
        auto zlm_server = stream->getMediaServer();
        if (zlm_server) {
            auto res = zlm_server->startRecordMp4(app, streamid, max_second);
            DebugL << res;
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto result =
                json_Mapper->readFromString<oatpp::Object<DTO::GETWAY::RecordResDto>>(res);
            if (result->code == 0 && result->result) {
                result->msg = "开始录制成功";
            }
            return result;
        }
    } else {
        auto result  = DTO::GETWAY::RecordResDto::createShared();
        result->code = -1;
        result->msg  = "stream not exist";
        return result;
    }
}

oatpp::Object<DTO::GETWAY::RecordResDto> stopRecord(const std::string &app,
                                                    const std::string &streamid) {
    GB28181::BaseStream::ptr stream = GB28181::g_StreamMgr::GetInstance()->getStream(streamid);
    if (stream) {
        auto zlm_server = stream->getMediaServer();
        if (zlm_server) {
            auto res = zlm_server->stopRecordMp4(app, streamid);
            DebugL << res;
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto result =
                json_Mapper->readFromString<oatpp::Object<DTO::GETWAY::RecordResDto>>(res);
            if (result->code == 0 && result->result) {
                result->msg = "停止录制成功";
            }
            return result;
        }
    } else {
        auto result  = DTO::GETWAY::RecordResDto::createShared();
        result->code = -1;
        result->msg  = "stream not exist";
        return result;
    }
}


oatpp::Object<DTO::GETWAY::RecordResDto> getRecordStatus(const std::string & app, const std::string &  streamid){
    GB28181::BaseStream::ptr stream = GB28181::g_StreamMgr::GetInstance()->getStream(streamid);
    if (stream) {
        auto zlm_server = stream->getMediaServer();
        if (zlm_server) {
            auto res = zlm_server->getRecordStatus(app, streamid);
            DebugL << res;
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto result =
                json_Mapper->readFromString<oatpp::Object<DTO::GETWAY::RecordResDto>>(res);
            if (result->code == 0 && result->result) {
                result->msg = "正在录制";
            }else{
                result->msg = "未录制";
            }
            return result;
        }
    } else {
        auto result  = DTO::GETWAY::RecordResDto::createShared();
        result->code = -1;
        result->msg  = "stream not exist";
        return result;
    }
}

oatpp::String getSnapShot(const oatpp::Object<DTO::GETWAY::StreamPlayDto>& streamPlayDto){
    auto zlm_server = ZLM::g_ZlmMgr::GetInstance()->getBestZlmServer();
    if(zlm_server){
        oatpp::String buff = zlm_server->getSnap(streamPlayDto->streamUrl);
        return buff;   
    }
    return "";
}

oatpp::Object<DTO::GETWAY::RecordResDto> setRecordSpeed(const std::string& path, const float speed){
    auto zlm_server = ZLM::g_ZlmMgr::GetInstance()->getBestZlmServer();
    if(zlm_server){
        auto res = zlm_server->setRecordSpeed(path, speed);
        DebugL << res;
        auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        auto result =
            json_Mapper->readFromString<oatpp::Object<DTO::GETWAY::RecordResDto>>(res);
        if (result->code == 0 && result->result) {
            result->msg = "设置播放速度成功";
        }
        return result;
    }



}




}  // namespace OP
