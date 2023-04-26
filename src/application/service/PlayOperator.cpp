#include "PlayOperator.hpp"
#include "gb28181/device/deviceManager.h"
#include "gb28181/request/call/invite_request.h"

#include "gb28181/device/base_stream.h"
#include "gb28181/device/call_session.h"
#include "gb28181/sip_server.h"
#include "zlmedia/zlmedia_server/zlm_manager.hpp"
namespace OP {

oatpp::Object<StatusDto> play_start(const std::string &deviceId, const std::string &channelId) {
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    auto status = StatusDto::createShared();
    if (!device) {
        status->code = 400;
        status->msg  = "该设备信息不存在";
        return status;
    }
    auto stream_sessioned =
        GB28181::g_StreamMgr::GetInstance()->getStream(deviceId + "_" + channelId);
    GB28181::InviteRequest::ptr req;
    if (stream_sessioned) {
        auto call_sessioned = std::dynamic_pointer_cast<GB28181::CallSession>(stream_sessioned);
        if (call_sessioned->isConnected()) {
            status->code = 400;
            status->msg  = "该设备已经被点播，请勿重复点播";
            return status;
        } else {
            req = std::make_shared<GB28181::InviteRequest>(device, channelId,
                                                           call_sessioned->getMediaServer());
        }
    } else {
        auto zlm_server = ZLM::g_ZlmMgr::GetInstance()->getBestZlmServer();
        if (!zlm_server) {
            status->code = 400;
            status->msg  = "当前没有可用的zlm服务器";
            return status;
        }
        req = std::make_shared<GB28181::InviteRequest>(device, channelId, zlm_server);
    }

    // GB28181::InviteRequest::ptr req = std::make_shared<GB28181::InviteRequest>(device, channelId,
    // zlm_server);
    req->send_call();
    auto call_session = GB28181::g_StreamMgr::GetInstance()->getStream(deviceId + "_" + channelId);
    if (call_session) {
        auto call_sessioned = std::dynamic_pointer_cast<GB28181::CallSession>(call_session);
        auto re             = call_sessioned->wait_for_stream_ready();
        if (!re) {
            status->code = 400;
            status->msg  = "点播超时";
            return status;
        }
    }
    status->code = 200;
    status->msg  = "点播成功";
    return status;
}

oatpp::Object<StatusDto> play_stop(const std::string &deviceId, const std::string &channelId) {
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    auto status = StatusDto::createShared();
    if (!device) {
        status->code = 400;
        status->msg  = "device not exist";
        return status;
    }
    eXosip_t *exconetxt = GB28181::g_SipServer::GetInstance()->GetExosipContext();
    if (exconetxt == nullptr) {
        status->code = 400;
        status->msg  = "exconetxt not exist";
        return status;
    }

    // 发送BYE请求
    auto stream_sessioned =
        GB28181::g_StreamMgr::GetInstance()->getStream(deviceId + "_" + channelId);
    if (stream_sessioned) {
        auto call_sessioned = std::dynamic_pointer_cast<GB28181::CallSession>(stream_sessioned);
        if (!call_sessioned->isConnected()) {
            status->code = 400;
            status->msg  = "改设备未被点播，无需停止点播";
            return status;
        }
        eXosip_call_terminate(exconetxt, call_sessioned->getCallId(),
                              call_sessioned->getDialogId());
        call_sessioned->setConnected(false);
    } else {
        status->code = 400;
        status->msg  = "改设备未被点播，无需停止点播";
        return status;
    }

    status->code = 200;
    status->msg  = "ok";
    return status;
}

oatpp::Object<DTO::GETWAY::StreamInfoDto>
play_stream_proxy(const oatpp::Object<DTO::GETWAY::StreamPlayDto> &streamPlayDto) {
    auto streamInfo = DTO::GETWAY::StreamInfoDto::createShared();
    auto zlm_server = ZLM::g_ZlmMgr::GetInstance()->getBestZlmServer();
    if (!zlm_server) {
        streamInfo->code = 400;
        streamInfo->msg  = "当前没有可用的zlm服务器";
        return streamInfo;
    }

    std::string app = "proxy";
    auto        stream_proxy =
        zlm_server->addStreamProxy(streamPlayDto->streamUrl, app, streamPlayDto->streamCode);
    if (!stream_proxy) {
        streamInfo->code = 400;
        streamInfo->msg  = "添加流代理失败";
        return streamInfo;
    }

    GB28181::g_StreamMgr::GetInstance()->makeStream(zlm_server->getZlmServerId(),
                                                    streamPlayDto->streamCode, app,
                                                    GB28181::STREAM_TYPE::STREAM_TYPE_PROXY);

    streamInfo->code = 200;
    streamInfo->msg  = "ok";

    // http://192.168.161.150:8080/index/api/webrtc?app=live&stream=test&type=play
    stringstream ss;
    ss << "http://" << zlm_server->getZlmAddr() << ":" << zlm_server->getZlmPort()
       << "/index/api/webrtc?app=" << app << "&stream=" << *streamPlayDto->streamCode
       << "&type=play";
    ss << "&token=" << zlm_server->getZlmSecret();
    streamInfo->playUrl = ss.str();
    return streamInfo;
}

}  // namespace OP
