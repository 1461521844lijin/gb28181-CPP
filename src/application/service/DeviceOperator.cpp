#include "DeviceOperator.hpp"

#include "gb28181/device_client/deviceManager.h"
#include "gb28181/request_manager/play_request.h"

namespace Web {

oatpp::Object<StatusDto> do_taks(const oatpp::Object<PlayDto> &playItem) {
    std::string deviceid = playItem->deviceId;

    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceid);

    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "device not exist";
        return status;
    }

    std::string op = playItem->op;
    if (op == "play") {
        GB28181::PlayRequest::SendInviteRequest(device);
    } else if (op == "bye") {
        GB28181::PlayRequest::SendByeRequest(device);
    }

    status->errorCode = 200;
    status->errorMsg  = "ok";

    return status;
}

}  // namespace Web
