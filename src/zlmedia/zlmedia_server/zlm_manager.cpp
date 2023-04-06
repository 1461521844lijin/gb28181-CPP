#include "zlm_manager.hpp"

#include "application/dto/configs/MediaConfigDto.hpp"
#include "oatpp/core/macro/component.hpp"

namespace ZLM {

void ZlmManager::addZlmServer(const std::string &zlm_addr,
                              int                zlm_port,
                              const std::string &zlm_secret,
                              const std::string &zlm_server_id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    ZlmServer::ptr zlm_server =
        std::make_shared<ZlmServer>(zlm_addr, zlm_port, zlm_secret, zlm_server_id);
    m_zlm_servers[zlm_server_id] = zlm_server;
}

void ZlmManager::removeZlmServer(const std::string &zlm_server_id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_zlm_servers.find(zlm_server_id) != m_zlm_servers.end()) {
        m_zlm_servers.erase(zlm_server_id);
    }
}

ZlmServer::ptr ZlmManager::getBestZlmServer() {
    std::lock_guard<std::mutex> lock(m_mutex);

    ZlmServer::ptr best_zlm_server = nullptr;
    int            min_load        = 0;
    for (auto &zlm_server : m_zlm_servers) {
        if (best_zlm_server == nullptr && zlm_server.second->getIsConnected()) {
            best_zlm_server = zlm_server.second;
            min_load        = best_zlm_server->getLoad();
        } else {
            if (zlm_server.second->getLoad() < min_load && zlm_server.second->getIsConnected()) {
                best_zlm_server = zlm_server.second;
                min_load        = best_zlm_server->getLoad();
            }
        }
    }
    return best_zlm_server;
}



void ZlmManager::updateZlmServerLoad() {
    // TODO 等后期多节点部署时，需要考虑负载均衡
    check_zlmload_timer.reset(new toolkit::Timer(
        60,
        [this]() {
           
            // TODO

            return true;
        },
        nullptr)
    );
}


void ZlmManager::updateZlmServerHeartbeat() {
    check_zlmheartbeat_timer.reset(new toolkit::Timer(
        60, 
        [this]() {
                std::lock_guard<std::mutex> lock(m_mutex);
                for (auto &zlm_server : m_zlm_servers) {
                    auto last_time = zlm_server.second->getLastHeartbeatTime();
                    if(time(NULL) - last_time > 60){  // 如果心跳超过60秒，认为流媒体服务器已经断开连接
                        zlm_server.second->setIsConnected(false);
                    }
                }
            return true;
        },
        nullptr)
    );
}


void ZlmManager::init() {
    // 启动两个定时器
    updateZlmServerLoad();
    updateZlmServerHeartbeat();


    OATPP_COMPONENT(oatpp::Object<MediaConfigDto>, media_config);

    addZlmServer(media_config->zlmAddr, media_config->zlmPort, media_config->zlmSecret, media_config->zlmServerID);








}




}  // namespace ZLM