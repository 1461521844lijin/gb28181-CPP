#include "PlayOperator.hpp"
#include "gb28181/device_client/deviceManager.h"
#include "gb28181/request/call/invite_request.h"

#include "gb28181/sip_server.h"
namespace OP {

oatpp::Object<StatusDto> play_start(const std::string &deviceId, const std::string &channelId) {
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);

    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "device not exist";
        return status;
    }

    GB28181::InviteRequest::ptr req = std::make_shared<GB28181::InviteRequest>(device, channelId);
    req->send_call();

    status->errorCode = 200;
    status->errorMsg  = "ok";
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
    eXosip_call_terminate(exconetxt, device->getCallId(), device->getDialogId());


    status->errorCode = 200;
    status->errorMsg  = "ok";
    return status;
}
}  // namespace GB28181
