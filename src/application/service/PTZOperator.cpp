#include "PTZOperator.hpp"

#include "gb28181/device/deviceManager.h"
#include "gb28181/request/message/ptzcontrol_request.h"
#include "gb28181/request/message/preset_request.h"
#include "gb28181/request/message/preset_ctl_request.h"

// #include "oatpp/web/protocol/http/Http.hpp"
#include <iostream>


namespace OP {


#define RETURN_ERROR(errorCode__, errorMsg__) \
    auto status__ = StatusDto::createShared(); \
    status__->errorCode = errorCode__; \
    status__->errorMsg = errorMsg__; \
    return status__;

oatpp::Object<StatusDto> ptz_ctl(const std::string &deviceId,
                                 const std::string &channelId,
                                 const std::string &command,
                                 int                speed) {


    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    if(!device){
        RETURN_ERROR(400, "device not exist");
    }
    // 控制指令,允许值: left, right, up, down, upleft, upright, downleft, downright, zoomin, zoomout, stop
    GB28181::PtzControlRequest::ptr req;
    if(command == "left"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 1, 0, 0, speed, 0);
    }else if(command == "right"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 2, 0, 0, speed, 0);
    }else if(command == "up"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 0, 1, 0, speed, 0);
    }else if(command == "down"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 0, 2, 0, speed, 0);
    }else if(command == "upleft"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 1, 1, 0, speed, 0);
    }else if(command == "upright"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 2, 1, 0, speed, 0);
    }else if(command == "downleft"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 1, 2, 0, speed, 0);
    }else if(command == "downright"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 2, 2, 0, speed, 0);
    }else if(command == "zoomin"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 0, 0, 1, 0, speed);
    }else if(command == "zoomout"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 0, 0, 2, 0, speed);
    }else if(command == "stop"){
        req = std::make_shared<GB28181::PtzControlRequest>(device, channelId, 0, 0, 0, 0, 0);
    }else{
        RETURN_ERROR(400, "command not support");
    }
        
    req->send_message();
    RETURN_ERROR(200, "ok");
}



oatpp::Object<StatusDto> preset_operate(const std::string& deviceId, const std::string& channelId, const std::string& command, const int presetIndex){

    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    if(!device){
        RETURN_ERROR(400, "device not exist");
    }
    if(command.empty() || presetIndex <= 0){
        RETURN_ERROR(400, "command or presetIndex error");
    }
    // 控制指令,允许值: set, goto, del   
    // TODO 设置预置位的index应该由后端决定，而不是前端传递
    GB28181::PresetCtlRequest::ptr req;
    if(command == "set"){
        req = std::make_shared<GB28181::PresetCtlRequest>(device, channelId, 129, 0, presetIndex, 0);
    }else if(command == "goto"){
        req = std::make_shared<GB28181::PresetCtlRequest>(device, channelId, 130, 0, presetIndex, 0);
    }else if(command == "del"){
        req = std::make_shared<GB28181::PresetCtlRequest>(device, channelId, 131, 0, presetIndex, 0);
    }else{
        RETURN_ERROR(400, "command not support");
    }
        
    req->send_message();
    RETURN_ERROR(200, "ok");


}

oatpp::Object<StatusDto> preset_query(const std::string& deviceId, const std::string& channelId){
    auto device = GB28181::g_deviceMgr::GetInstance()->getDevice(deviceId);
    if(!device){
        RETURN_ERROR(400, "device not exist");
    }
    GB28181::PresetRequest::ptr req = std::make_shared<GB28181::PresetRequest>(device, channelId);
    req->send_message();
    req->SetWait();
    req->WaitResult();
    if(!req->IsFinished()){
        RETURN_ERROR(400, "query preset timeout");
    }
    auto preset_list = req->get_preset_list();
    for(auto it = preset_list.begin(); it != preset_list.end(); it++){
        std::cout << "preset index: " << it->first << " preset name: " << it->second << std::endl;
    }

    RETURN_ERROR(200, "ok");
}









}  // namespace OP