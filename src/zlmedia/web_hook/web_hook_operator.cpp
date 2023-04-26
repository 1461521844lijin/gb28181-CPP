#include "web_hook_operator.hpp"
#include "Util/logger.h"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "utils/url_code.h"

#include "gb28181/device/base_stream.h"
#include "gb28181/device/call_session.h"
#include "gb28181/device/stream.h"
#include "zlmedia/zlmedia_server/zlm_manager.hpp"


namespace ZLM {

#define HTTP_RETYRN_CODE(__code, __msg)                                                            \
    auto response  = DTO::ZLM::ResponseDto::createShared();                                        \
    response->code = __code;                                                                       \
    response->msg  = __msg;                                                                        \
    return response;

oatpp::Object<DTO::ZLM::ResponseDto> on_server_keepalive_api(
    const oatpp::Object<DTO::ZLM::OnServerKeepaliveDto> &onServerKeepaliveTiem) {
    // InfoL <<"[ZLM] "<< "on_server_keepalive:" << *onServerKeepaliveTiem->mediaServerId;
    if (onServerKeepaliveTiem->mediaServerId == nullptr) {
        ErrorL << "on_server_keepalive mediaServerId is null";
        return nullptr;
    }
    std::string mediaServerId = onServerKeepaliveTiem->mediaServerId;
    g_ZlmMgr::GetInstance()->updateZlmServerHeartbeat(mediaServerId);
    auto response = DTO::ZLM::ResponseDto::createShared();
    return response;
}

// 默认从zlm推送的流新增事件的id是唯一的，流id唯一性判断已经在业务接口层实现
oatpp::Object<DTO::ZLM::ResponseDto>
on_stream_changed_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO> &onStreamChangedTiem) {
    // InfoL << "on_stream_changed:";
    auto        response      = DTO::ZLM::ResponseDto::createShared();
    std::string app           = onStreamChangedTiem->app;
    std::string stream        = onStreamChangedTiem->stream;
    std::string schema        = onStreamChangedTiem->schema;
    std::string vhost         = onStreamChangedTiem->vhost;
    std::string mediaServerId = onStreamChangedTiem->mediaServerId;

    if (onStreamChangedTiem->regist) {  // 注册逻辑
        switch (onStreamChangedTiem->originType) {
            case 3: {  // rtp_push
                auto stream_session = GB28181::g_StreamMgr::GetInstance()->getStream(stream);
                if (stream_session) {
                    auto call_session =
                        std::dynamic_pointer_cast<GB28181::CallSession>(stream_session);
                    call_session->notify_stream_ready();
                }
                InfoL << "[ZLM] "
                      << "国标流注册:" << app << " " << stream << " " << schema << " " << vhost
                      << " " << mediaServerId;
                break;
            }
            case 4: {  // pull
                GB28181::g_StreamMgr::GetInstance()->makeStream(
                    mediaServerId, app, stream, GB28181::STREAM_TYPE::STREAM_TYPE_PROXY);
                InfoL << "拉流代理注册 : " << schema << " " << app << " " << stream << " "
                      << mediaServerId;
                break;
            }
            default: {  // 其他推流类型
                InfoL << "[ZLM] "
                      << "其他流注册:" << app << " " << stream << " " << schema << " " << vhost
                      << " " << mediaServerId;
                GB28181::g_StreamMgr::GetInstance()->makeStream(
                    mediaServerId, app, stream, GB28181::STREAM_TYPE::STREAM_TYPE_PUSH);
                break;
            }
        }
    } else {  // 注销逻辑
        auto stream_session = GB28181::g_StreamMgr::GetInstance()->getStream(stream);
        if (stream_session) {
            if (stream_session->getType() == GB28181::STREAM_TYPE::STREAM_TYPE_GB) {
                InfoL << "[ZLM] 国标流注销：" << app << " " << stream << " " << mediaServerId;
                // GB28181::g_StreamMgr::GetInstance()->removeStream(stream);
            }
            if (stream_session->getType() == GB28181::STREAM_TYPE::STREAM_TYPE_PROXY) {
                InfoL << "[ZLM] 拉流代理注销" << app << " " << stream << " " << mediaServerId;
                // GB28181::g_StreamMgr::GetInstance()->removeStream(stream);
            }
            if (stream_session->getType() == GB28181::STREAM_TYPE::STREAM_TYPE_PUSH) {
                InfoL << "[ZLM] 推流代理注销" << app << " " << stream << " " << mediaServerId;
                // GB28181::g_StreamMgr::GetInstance()->removeStream(stream);
            }
        }
    }

    response->code = 0;
    response->msg  = "success";
    return response;
}

oatpp::Object<DTO::ZLM::ResponseDto>
on_stream_none_reader_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO> &onStreamChangedTiem) {
    std::string app           = onStreamChangedTiem->app;
    std::string stream        = onStreamChangedTiem->stream;
    std::string schema        = onStreamChangedTiem->schema;
    std::string vhost         = onStreamChangedTiem->vhost;
    std::string mediaServerId = onStreamChangedTiem->mediaServerId;

    InfoL << "[ZLM] 流无人观看流:" << app << " " << stream << " " << mediaServerId;
    // GB28181::g_StreamMgr::GetInstance()->removeStream(stream);
    auto response   = DTO::ZLM::ResponseDto::createShared();
    response->code  = 0;
    response->msg   = "success";
    response->close = true;

    return response;
}

oatpp::Object<DTO::ZLM::ResponseDto>
on_publish_api(const oatpp::Object<DTO::ZLM::OnPublishDTO> &onPublishItem) {
    std::string app           = onPublishItem->app;
    std::string stream        = onPublishItem->stream;
    std::string schema        = onPublishItem->schema;
    std::string vhost         = onPublishItem->vhost;
    std::string mediaServerId = onPublishItem->mediaServerId;
    std::string ip            = onPublishItem->ip;
    std::string params        = onPublishItem->params;

    InfoL << "[ZLM] 推流鉴权事件:" << app << " " << stream << " " << ip << " " << params;

    auto param_map = Tools::Parse_param(params);
    // 由系统本身发起的rtp推流，不需要鉴权
    if (GB28181::g_StreamMgr::GetInstance()->getStream(stream)) {
        HTTP_RETYRN_CODE(0, "success");
    }
    auto zlm = g_ZlmMgr::GetInstance()->getZlmServer(mediaServerId);
    if (zlm) {
        if (zlm->getZlmSecret() == param_map["token"]) {
            HTTP_RETYRN_CODE(0, "success");
        }
    }
    HTTP_RETYRN_CODE(-1, "鉴权参数与zlm不匹配");
}

oatpp::Object<DTO::ZLM::ResponseDto>
on_play_api(const oatpp::Object<DTO::ZLM::OnPublishDTO> &onPublishItem) {
    std::string app           = onPublishItem->app;
    std::string stream        = onPublishItem->stream;
    std::string schema        = onPublishItem->schema;
    std::string vhost         = onPublishItem->vhost;
    std::string mediaServerId = onPublishItem->mediaServerId;
    std::string ip            = onPublishItem->ip;
    std::string params        = onPublishItem->params;

    InfoL << "[ZLM] 播放鉴权事件:" << app << " " << stream << " " << mediaServerId << " " << ip
          << " " << params;

    auto param_map = Tools::Parse_param(params);
    // GB28181::g_StreamMgr::GetInstance()->removeStream(stream);
    // http://192.168.161.150:8080/index/api/webrtc?app=rtp&stream=62000000001320000002_62000000001320000011&type=play&token=035c73f7-bb6b-4889-a715-d9eb2d1925cc

    auto zlm = g_ZlmMgr::GetInstance()->getZlmServer(mediaServerId);
    if(!zlm){
        HTTP_RETYRN_CODE(-1, "zlm不存在");
    }
    if(zlm->getZlmSecret() == param_map["token"]){
        HTTP_RETYRN_CODE(0, "success");
    }else{
        HTTP_RETYRN_CODE(-1, "鉴权参数与zlm不匹配");
    }
    HTTP_RETYRN_CODE(-1, "鉴权不通过");



    // if (GB28181::g_StreamMgr::GetInstance()->getStream(stream)) {
    //     auto zlm = g_ZlmMgr::GetInstance()->getZlmServer(mediaServerId);
    //     if (zlm) {
    //         if (zlm->getZlmSecret() == param_map["token"]) {
    //             InfoL << "[ZLM] 播放鉴权成功:" << app << " " << stream << " " << ip << " "
    //                   << params;
    //             HTTP_RETYRN_CODE(0, "success");
    //         } else {
    //             InfoL << "[ZLM] 播放鉴权失败, 鉴权未通过:" << app << " " << stream << " " << ip << " "
    //                   << params;
    //             HTTP_RETYRN_CODE(-1, "鉴权参数与zlm不匹配");
    //         }
    //     } else {
    //         InfoL << "[ZLM] 播放鉴失败, 流媒体服务器不存在:" << app << " " << stream << " " << ip << " " << params;
    //         HTTP_RETYRN_CODE(-1, "zlm不存在");
    //     }
    // } else {
    //     InfoL << "[ZLM] 播放鉴权失败, 流不存在:" << app << " " << stream << " " << ip << " " << params;
    //     HTTP_RETYRN_CODE(-1, "流不存在");
    // }
}

}  // namespace ZLM
