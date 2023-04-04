#include "PTZOperator.hpp"

#include "gb28181/device_client/deviceManager.h"
#include "gb28181/request/message/ptzcontrol_request.h"
#include "gb28181/request/message/preset_request.h"
#include "gb28181/request/message/preset_ctl_request.h"

// #include "oatpp/web/protocol/http/Http.hpp"



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

}  // namespace OP