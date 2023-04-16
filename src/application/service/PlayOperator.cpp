#include "PlayOperator.hpp"
#include "gb28181/device/deviceManager.h"
#include "gb28181/request/call/invite_request.h"

#include "zlmedia/zlmedia_server/zlm_manager.hpp"
#include "gb28181/device/call_session.h"
#include "gb28181/sip_server.h"
namespace OP {

oatpp::Object<StatusDto> play_start(const std::string &deviceId, const std::string &channelId) {
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);

    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "该设备信息不存在";
        return status;
    }
    auto call_sessioned = GB28181::g_CallSessionMgr::GetInstance()->getCallSession(deviceId);
    if(call_sessioned && call_sessioned->isConnected()){
        status->errorCode = 400;
        status->errorMsg  = "该设备已经被点播，请勿重复点播";
        return status;
    }
    auto zlm_server = ZLM::g_ZlmMgr::GetInstance()->getBestZlmServer();
    if(!zlm_server){
        status->errorCode = 400;
        status->errorMsg  = "当前没有可用的zlm服务器";
        return status;
    }

    GB28181::InviteRequest::ptr req = std::make_shared<GB28181::InviteRequest>(device, channelId, zlm_server);
    req->send_call();
    auto call_session = GB28181::g_CallSessionMgr::GetInstance()->getCallSession(deviceId);
    auto re = call_session->wait_for_stream_ready();
    if(!re){
        status->errorCode = 400;
        status->errorMsg  = "点播超时";
        return status;
    }
    status->errorCode = 200;
    status->errorMsg  = "点播成功";
    return status;
}

oatpp::Object<StatusDto> play_stop(const std::string &deviceId, const std::string &channelId) {
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);

    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "device not exist";
        return status;
    }
    eXosip_t * exconetxt = GB28181::g_SipServer::GetInstance()->GetExosipContext();
    if (exconetxt == nullptr) {
        status->errorCode = 400;
        status->errorMsg  = "exconetxt not exist";
        return status;
    }

    // 发送BYE请求
    auto call_session = GB28181::g_CallSessionMgr::GetInstance()->getCallSession(deviceId);
    if(!call_session || !call_session->isConnected()){
        status->errorCode = 200;
        status->errorMsg  = "改设备没有被点播，无需停止";
        return status;
    }
    eXosip_call_terminate(exconetxt, call_session->getCallId(), call_session->getDialogId());
    call_session->setConnected(false);

    status->errorCode = 200;
    status->errorMsg  = "ok";
    return status;
}
}  // namespace GB28181
