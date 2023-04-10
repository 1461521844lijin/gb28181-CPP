#include "keepalive_handler.h"
#include "gb28181/device/deviceManager.h"
#include "utils/CommonTools.h"
#include "glog/logging.h"
namespace GB28181
{

// 收到对应设备的心跳后, 更新缓存中的历史心跳信息
int KeepaliveHandler::handle(SipEvent::ptr event, tinyxml2::XMLDocument& xml)
{
    // LOG(INFO) << "KeepaliveHandler::handle";
    std::string devicdId = xml.FirstChildElement("Notify")->FirstChildElement("DeviceID")->GetText();
    if(!devicdId.empty()){
        g_deviceMgr::GetInstance()->updateDeviceStatus(devicdId, 1);
        g_deviceMgr::GetInstance()->updateDeviceLastTime(devicdId, Time2Str());
        return sendSimplyResp(devicdId.c_str(), event->excontext, event->exevent->tid, SIP_OK);
    }
}

}