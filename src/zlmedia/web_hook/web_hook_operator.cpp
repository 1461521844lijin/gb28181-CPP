#include "web_hook_operator.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "glog/logging.h"

#include "zlmedia/zlmedia_server/zlm_manager.hpp"

namespace ZLM
{

oatpp::Object<DTO::ZLM::ResponseDto> on_server_keepalive_api(const oatpp::Object<DTO::ZLM::OnServerKeepaliveDto>& onServerKeepaliveTiem){


    // LOG(INFO) <<"[ZLM] "<< "on_server_keepalive:" << *onServerKeepaliveTiem->mediaServerId;

    if(onServerKeepaliveTiem->mediaServerId == nullptr){
        LOG(ERROR) << "on_server_keepalive mediaServerId is null";
        return nullptr;
    }
    std::string mediaServerId = onServerKeepaliveTiem->mediaServerId;
    g_ZlmMgr::GetInstance()->updateZlmServerHeartbeat(mediaServerId);

    auto response = DTO::ZLM::ResponseDto::createShared();
    return response;
}


oatpp::Object<DTO::ZLM::ResponseDto>  on_stream_changed_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO>& onStreamChangedTiem){

    // LOG(INFO) << "on_stream_changed:";
    

    auto response = DTO::ZLM::ResponseDto::createShared();
    if(onStreamChangedTiem->regist){
        
        std::string app = onStreamChangedTiem->app;
        std::string stream = onStreamChangedTiem->stream;
        std::string schema = onStreamChangedTiem->schema;
        std::string vhost = onStreamChangedTiem->vhost;
        std::string mediaServerId = onStreamChangedTiem->mediaServerId;


        LOG(INFO) <<"[ZLM] "<< "on_stream_changed regist:" << app << " " << stream << " " << schema << " " << vhost << " " << mediaServerId;

        response->code = 0;
        response->msg = "success";
    }else{
        LOG(INFO) << "on_stream_changed unregist";
        response->code = 0;
        response->msg = "success";
    }



    return response;




}













    
} // namespace ZLM
