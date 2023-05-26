#include "DeviceOperator.hpp"

#include "gb28181/device/deviceManager.h"
#include "gb28181/request/message/homeposition_request.h"
#include "gb28181/request/message/guard_request.h"

namespace OP {

oatpp::List<oatpp::Object<DTO::GETWAY::DeviceInfoDto>> get_device_list() {
    oatpp::List<oatpp::Object<DTO::GETWAY::DeviceInfoDto>> device_list =
        oatpp::List<oatpp::Object<DTO::GETWAY::DeviceInfoDto>>::createShared();
    auto devices = GB28181::g_deviceMgr::GetInstance()->getDeviceList();
    for (auto device : devices) {
        auto device_info                  = DTO::GETWAY::DeviceInfoDto::createShared();
        device_info->device_id            = device->getDeviceId();
        device_info->device_name          = device->getName();
        device_info->device_ip            = device->getIp();
        device_info->device_port          = device->getPort();
        device_info->device_transport     = device->getTransport();
        device_info->device_status        = device->getStatus();
        device_info->device_regiest_time  = device->getRegiestTime();
        device_info->device_last_time     = device->getLastTime();
        device_info->device_channel_count = device->getChannelCount();
        device_list->push_back(device_info);
    }
    return device_list;
}

oatpp::Object<StatusDto> home_position(const std::string &deviceId,
                                       const std::string &channelId,
                                       const int          enabled,
                                       const int          presetIndex,
                                       const int          resetTime) {
    auto status = StatusDto::createShared();
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    if (device == nullptr) {
        status->code = -1;
        status->msg  = "device not found";
        return status;
    }
    auto request = std::make_shared<GB28181::HomePositionRequest>(device, channelId, enabled,
                                                                  presetIndex, resetTime);
    request->send_message();

    status->code = 0;
    status->msg  = "ok";
    return status;
}

oatpp::Object<StatusDto> device_guard(const std::string &deviceId, const std::string &guardCmdStr) {

    auto status = StatusDto::createShared();
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    if (device == nullptr) {
        status->code = -1;
        status->msg  = "device not found";
        return status;
    }
    auto request = std::make_shared<GB28181::GuardRequest>(device, guardCmdStr);
    request->send_message();
    request->SetWait();
    request->WaitResult();

    auto re = request->IsFinished();
    if(re){
        status->code = 0;
        status->msg  = "ok";
    }else{
        status->code = -1;
        status->msg  = "请求超时";
    }


    return status;



}

}  // namespace OP