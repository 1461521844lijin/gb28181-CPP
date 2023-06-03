//
// Created by lijin on 2023/6/2.
//
#include "Util/logger.h"
#include "platformManger.hpp"

namespace GB28181 {

void PlatformManger::addPlatform(const Platform::ptr& platform) {
    std::lock_guard<std::mutex> lock(m_platform_mutex);
    m_platform_map[platform->getDeviceId()] = platform;
}

void PlatformManger::removePlatform(const std::string &platformId) {
    std::lock_guard<std::mutex> lock(m_platform_mutex);
    if(m_platform_map.find(platformId) != m_platform_map.end()){
        m_platform_map.erase(platformId);
    } else{
        WarnL << "platformId:" << platformId << " not exist";
    }
}

Platform::ptr PlatformManger::getPlatform(const std::string &platformId) {
    std::lock_guard<std::mutex> lock(m_platform_mutex);
    auto                        it = m_platform_map.find(platformId);
    if (it != m_platform_map.end()) {
        return it->second;
    }
    return nullptr;
}

Platform::ptr PlatformManger::getPlatformByRid(int rid) {
    std::lock_guard<std::mutex> lock(m_platform_mutex);
    for (auto it = m_platform_map.begin(); it != m_platform_map.end(); ++it) {
        if (it->second->get_rid() == rid) {
            return it->second;
        }
    }
    return nullptr;
}









}  // namespace GB28181