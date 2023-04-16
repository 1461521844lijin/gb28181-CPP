#include "web_hook_operator.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "Util/logger.h"

#include "zlmedia/zlmedia_server/zlm_manager.hpp"
#include "gb28181/device/call_session.h"
#include "gb28181/device/stream_proxy.h"


namespace ZLM
{

oatpp::Object<DTO::ZLM::ResponseDto> on_server_keepalive_api(const oatpp::Object<DTO::ZLM::OnServerKeepaliveDto>& onServerKeepaliveTiem){
    // InfoL <<"[ZLM] "<< "on_server_keepalive:" << *onServerKeepaliveTiem->mediaServerId;
    if(onServerKeepaliveTiem->mediaServerId == nullptr){
        ErrorL << "on_server_keepalive mediaServerId is null";
        return nullptr;
    }
    std::string mediaServerId = onServerKeepaliveTiem->mediaServerId;
    g_ZlmMgr::GetInstance()->updateZlmServerHeartbeat(mediaServerId);
    auto response = DTO::ZLM::ResponseDto::createShared();
    return response;
}


oatpp::Object<DTO::ZLM::ResponseDto>  on_stream_changed_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO>& onStreamChangedTiem){
    // InfoL << "on_stream_changed:";
    auto response = DTO::ZLM::ResponseDto::createShared();
    std::string app = onStreamChangedTiem->app;
    std::string stream = onStreamChangedTiem->stream;
    std::string schema = onStreamChangedTiem->schema;
    std::string vhost = onStreamChangedTiem->vhost;
    std::string mediaServerId = onStreamChangedTiem->mediaServerId;
   
    switch (onStreamChangedTiem->originType)
    {
    case 3: { // rtp_push
        auto call_session = GB28181::g_CallSessionMgr::GetInstance()->getCallSession(stream.substr(0,stream.find("_")));
        if(onStreamChangedTiem->regist){
            if(call_session){
                call_session->addStream(stream,app,schema);
                call_session->notify_stream_ready();
            }
            InfoL <<"[ZLM] "<< "国标流注册:" << app << " " << stream << " " << schema << " " << vhost << " " << mediaServerId;
            response->code = 0;
            response->msg = "success";
        }else{
            if(call_session){
                call_session->removeStream(schema);
            }
            InfoL << "[ZLM] 国标流注销";
            response->code = 0;
            response->msg = "success";
        }    
        break;
    }     
    case 4: { // pull
        // auto stream_proxy = GB28181::g_StreamProxyMgr::GetInstance()->getStreamProxy()
        if(onStreamChangedTiem->regist){
            GB28181::StreamProxy::ptr stream_proxy = std::make_shared<GB28181::StreamProxy>(mediaServerId, app, stream);
            GB28181::g_StreamProxyMgr::GetInstance()->addStreamProxy(stream_proxy);
            InfoL << "拉流代理注册 : " << schema << " " << app << " " << stream << " " << mediaServerId;
            response->code = 0;
            response->msg = "success";
        }else{
            GB28181::g_StreamProxyMgr::GetInstance()->removeStreamProxy(mediaServerId, stream);
            InfoL << "拉流代理注销 : " << schema << " " << app << " " << stream << " " << mediaServerId;
            response->code = 0;
            response->msg = "success";
        }
        break;
    }
    default:
        break;
    }
    

    return response;
}

oatpp::Object<DTO::ZLM::ResponseDto>  on_stream_none_reader_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO>& onStreamChangedTiem){

    std::string app = onStreamChangedTiem->app;
    std::string stream = onStreamChangedTiem->stream;
    std::string schema = onStreamChangedTiem->schema;
    std::string vhost = onStreamChangedTiem->vhost;
    std::string mediaServerId = onStreamChangedTiem->mediaServerId;

    InfoL << "on_stream_none_reader:" << app << " " << stream << " " << schema << " " << vhost << " " << mediaServerId;

    auto response = DTO::ZLM::ResponseDto::createShared();
    response->code = 0;
    response->msg = "success";
    response->close = true;

    return response;
}











    
} // namespace ZLM
