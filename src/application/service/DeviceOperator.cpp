#include "DeviceOperator.hpp"

#include "gb28181/device_client/deviceManager.h"
#include "gb28181/request/play_request.h"
#include "gb28181/request/message/ptzcontrol_request.h"
#include "gb28181/request/message/preset_request.h"
#include "gb28181/request/message/preset_ctl_request.h"
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


 oatpp::Object<StatusDto> ptz_ctl(const oatpp::Object<PtzDto>& ptzItem){



    std::string deviceid = ptzItem->deviceId;

    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceid);

    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "device not exist";
        return status;
    }

    int leftright = ptzItem->leftRight;
    int updown = ptzItem->upDown;
    int inOut = ptzItem->inOut;
    int move = ptzItem->moveSpeed;
    int zoom = ptzItem->zoomSpeed;

    std::string channelId = ptzItem->channelId;


    GB28181::PtzControlRequest::ptr req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, leftright, updown, inOut, move, zoom);
    req->send_message(true);

    status->errorCode = 200;
    status->errorMsg  = "ok";

    return status;
 }


 oatpp::Object<StatusDto> preset_control(const oatpp::Object<PlayDto>& playItem){

    std::string deviceid = playItem->deviceId;
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceid);
    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "device not exist";
        return status;
    }
    std::string channelId = playItem->channelId;
    std::string op = playItem->op;
    int presetId = playItem->presetId;

    GB28181::PresetCtlRequest::ptr req;
    if(op == "set"){
        req = std::make_shared<GB28181::PresetCtlRequest>(device, channelId, 129, 0, presetId, 0);
    }else if (op == "goto"){
        req = std::make_shared<GB28181::PresetCtlRequest>(device, channelId, 130, 0, presetId, 0);
    }else if (op == "del"){
        req = std::make_shared<GB28181::PresetCtlRequest>(device, channelId, 131, 0, presetId, 0);
    }
    req->send_message(true);

    status->errorCode = 200;
    status->errorMsg  = "ok";

    return status;
 }


 oatpp::Object<StatusDto> preset_quire(const oatpp::Object<PlayDto>& playItem){

    std::string deviceid = playItem->deviceId;
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceid);
    auto status = StatusDto::createShared();
    if (!device) {
        status->errorCode = 400;
        status->errorMsg  = "device not exist";
        return status;
    }
    std::string channelId = playItem->channelId;


    GB28181::PresetRequest::ptr req = std::make_shared<GB28181::PresetRequest>(device, channelId);
    req->send_message(true);

    status->errorCode = 200;
    status->errorMsg  = "ok";

    return status;
 }



}  // namespace Web
