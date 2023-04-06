#pragma once

#include <map>
#include <memory>

#include "Poller/Timer.h"
#include "zlm_server.hpp"
#include "utils/Singleton.h"

namespace ZLM {

class ZlmManager {
private:
    std::mutex m_mutex;

    toolkit::Timer::Ptr check_zlmload_timer;       // 更新流媒体服务器负载定时器
    toolkit::Timer::Ptr check_zlmheartbeat_timer;  // 更新流媒体服务器负载定时器

    // mediaId -> ZlmServer
    std::map<std::string, ZlmServer::ptr> m_zlm_servers;

public:
    void init();

    void addZlmServer(const std::string &zlm_addr,
                      int                zlm_port,
                      const std::string &zlm_secret,
                      const std::string &zlm_server_id);

    void removeZlmServer(const std::string &zlm_server_id);

    // 获取负载最小的流媒体服务器
    ZlmServer::ptr getBestZlmServer();


private:
    // 更新流媒体服务器负载
    void updateZlmServerLoad();

    // 更新流媒体服务器心跳
    void updateZlmServerHeartbeat();
};

typedef Tools::Singleton<ZlmManager> g_ZlmMgr;

}  // namespace ZLM