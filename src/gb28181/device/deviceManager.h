#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "device.h"
#include "utils/Singleton.h"
#include "Poller/Timer.h"
namespace GB28181 {

class DeviceManager {
public:
    typedef std::shared_ptr<DeviceManager> ptr;

private:
    std::mutex m_mutex;
    // 设备id -> 设备对象
    std::unordered_map<std::string, Device::ptr> m_device_map;
    toolkit::Timer::Ptr check_device_timer;  // 更新设备状态定时器

    // 更新设备状态
    void checkDeviceStatusTimer();


public:
    DeviceManager()  = default;
    ~DeviceManager() = default;

    void init();

    void        addDevice(Device::ptr device);
    Device::ptr getDevice(const std::string &deviceId);
    void        removeDevice(std::string &deviceId);

    // 获取设备列表
    std::vector<Device::ptr> getDeviceList();

    // 获取设备数量
    int getDeviceCount();

    // 更新设备在线状态
    void updateDeviceStatus(std::string &deviceId, int status);

    // 更新设备最后一次心跳时间
    void updateDeviceLastTime(std::string &deviceId, std::string lastTime);

    // 更新设备通道数
    void updateDeviceChannelCount(std::string &deviceId, int channelCount);
};

typedef Tools::Singleton<DeviceManager> g_deviceMgr;

}  // namespace GB28181