#include "zlm_server.hpp"

namespace ZLM {

std::string &ZlmServer::getZlmAddr() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_zlm_addr;
}
void ZlmServer::setZlmAddr(std::string &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_zlm_addr = value;
}

int ZlmServer::getZlmPort() {
    return m_zlm_port;
}
void ZlmServer::setZlmPort(int value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_zlm_port = value;
}

std::string &ZlmServer::getZlmSecret() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_zlm_secret;
}
void ZlmServer::setZlmSecret(std::string &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_zlm_secret = value;
}

std::string &ZlmServer::getZlmServerId() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_zlm_server_id;
}
void ZlmServer::setZlmServerId(std::string &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_zlm_server_id = value;
}

bool ZlmServer::getIsConnected() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_is_connected;
}
void ZlmServer::setIsConnected(bool value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_is_connected = value;
}

int ZlmServer::getLoad() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_load;
}
void ZlmServer::setLoad(int value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_load = value;
}

time_t ZlmServer::getLastHeartbeatTime() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_last_heartbeat_time;
}
void ZlmServer::setLastHeartbeatTime(time_t value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_last_heartbeat_time = value;
}


}  // namespace ZLM