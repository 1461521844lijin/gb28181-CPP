#pragma once

#include "gb28181/device_client/device.h"
#include "eXosip2/eXosip.h"
namespace GB28181 {




    // 与国标设备播放相关的请求
    class PlayRequest
    {
    public:
        PlayRequest(/* args */) = default;
        ~PlayRequest() = default;

    /**
     * @brief 向设备发送播放请求
     * 
     * @param device 国标设备对象指针
     * @param exconetxt exosip上下文
     * @return int 
     */
    static int SendInviteRequest(Device::ptr device, eXosip_t * exconetxt = nullptr);

    /**
     * @brief 向设备发送停止播放请求
     * 
     * @param device 国标设备对象指针
     * @param exconetxt exosip上下文
     * @return int 
     */
    static int SendByeRequest(Device::ptr device, eXosip_t * exconetxt = nullptr);

    /**
     * @brief 向设备发送暂停播放请求
     * 
     * @param device 国标设备对象指针
     * @param exconetxt exosip上下文
     * @return int 
     */
    static int SendPauseRequest(Device::ptr device, eXosip_t * exconetxt = nullptr);

    /**
     * @brief 向设备发送恢复播放请求
     * 
     * @param device 国标设备对象指针
     * @param exconetxt exosip上下文
     * @return int 
     */
    static int SendResumeRequest(Device::ptr device, eXosip_t * exconetxt = nullptr);

    };
}