#include "deviceManager.h"

namespace GB28181 {


void DeviceManager::addDevice(Device::ptr device) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_device_map[device->getDeviceId()] = device;
}

Device::ptr DeviceManager::getDevice(std::string& deviceId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_device_map.find(deviceId);
    if (it != m_device_map.end()) {
        return it->second;
    }
    return nullptr;
}

void DeviceManager::removeDevice(std::string& deviceId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_device_map.erase(deviceId);
}

std::vector<Device::ptr> DeviceManager::getDeviceList() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<Device::ptr> deviceList;
    for (auto it = m_device_map.begin(); it != m_device_map.end(); ++it) {
        deviceList.push_back(it->second);
    }
    return deviceList;
}

int DeviceManager::getDeviceCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_device_map.size();
}

void DeviceManager::updateDeviceStatus(std::string& deviceId, int status) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_device_map.find(deviceId);
    if (it != m_device_map.end()) {
        it->second->setStatus(status);
    }
}

void DeviceManager::updateDeviceLastTime(std::string& deviceId, std::string lastTime) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_device_map.find(deviceId);
    if (it != m_device_map.end()) {
        it->second->setLastTime(lastTime);
    }
}

void DeviceManager::updateDeviceChannelCount(std::string& deviceId, int channelCount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_device_map.find(deviceId);
    if (it != m_device_map.end()) {
        it->second->setChannelCount(channelCount);
    }
}

} // namespace GB28181