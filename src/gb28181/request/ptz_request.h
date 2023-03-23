#pragma once


#include "gb28181/device_client/device.h"

namespace GB28181
{

class PtzRequest
{
private:
    /* data */
public:
    PtzRequest(/* args */) = default;
    ~PtzRequest() = default;

    /**
     * @brief 向设备发送云台控制请求
     * 
     * @param device        国标设备对象指针
     * @param leftRight     镜头左移右移 0:停止 1:左移 2:右移
     * @param upDown        镜头上移下移 0:停止 1:上移 2:下移
     * @param inOut         镜头放大缩小 0:停止 1:缩小 2:放大
     * @param moveSpeed     镜头移动速度 默认 0XFF (0-255)
     * @param zoomSpeed     镜头缩放速度 默认 0X1 (0-255)
     * @return int 
     */
    static int SendPtzRequest(Device::ptr device, int leftRight, int upDown, int inOut, int moveSpeed, int zoomSpeed);



};









    
} // namespace GB28181










