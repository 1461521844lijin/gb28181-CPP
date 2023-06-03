//
// Created by lijin on 2023/6/2.
//

#ifndef GB28181_CPP_PLATFORMMANGER_HPP
#define GB28181_CPP_PLATFORMMANGER_HPP

#include "platform.h"
#include <mutex>
#include "utils/Singleton.h"

namespace GB28181 {

class PlatformManger{
private:
    std::unordered_map<std::string, Platform::ptr> m_platform_map;
    std::mutex m_platform_mutex;
public:
    PlatformManger() = default;
    ~PlatformManger() = default;

    void addPlatform(const Platform::ptr& platform);
    void removePlatform(const std::string &platformId);

    Platform::ptr getPlatform(const std::string &platformId);
    Platform::ptr getPlatformByRid(int rid);

};

typedef Tools::Singleton<PlatformManger> g_platformMgr;

}  // namespace GB28181

#endif  // GB28181_CPP_PLATFORMMANGER_HPP
