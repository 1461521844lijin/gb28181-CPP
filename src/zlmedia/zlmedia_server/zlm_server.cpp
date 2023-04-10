#include "zlm_server.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "utils/httplib.h"
#include "zlmedia/dto/open_rtp_server_dto.hpp"

#include "glog/logging.h"

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

SSRCConfig::ptr ZlmServer::getSsrcConfig() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_ssrc_config;
}

void ZlmServer::setSsrcConfig(SSRCConfig::ptr value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_ssrc_config = value;
}

SSRCInfo::ptr ZlmServer::openRTPServer(const std::string &streamid, bool isPlayback) {
    // 申请rtp端口
    int             port = 0;
    std::string     ssrc;
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::string     path = "/index/api/openRtpServer?secret=" + m_zlm_secret +
                       "&port=-1&tcp_mode=1&stream_id=" + streamid;
    LOG(INFO) << "openRTPServer path: " << path;
    try {
        auto res = cli.Post(path.c_str());
        if (res->status == 200) {
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto res_obj =
                json_Mapper->readFromString<oatpp::Object<DTO::ZLM::openRtpServerRes>>(res->body);
            if(res_obj->code == 0){
                port = res_obj->port;
            }else{
                LOG(ERROR) << "openRTPServer failed: " << *res_obj->msg;
                return nullptr;
            }
        }
        if (port == 0) {
            LOG(ERROR) << "openRTPServer failed: port is 0";
            return nullptr;
        }
    } catch (const std::exception &e) {
        LOG(ERROR) << "openRTPServer failed: " << e.what();
        return nullptr;
    }
    

    if (!isPlayback) {
        ssrc = m_ssrc_config->getPlaySsrc();
    } else {
        ssrc = m_ssrc_config->getPlayBackSsrc();
    }

    SSRCInfo::ptr ssrcInfo = std::make_shared<SSRCInfo>(port, ssrc, streamid);
    return ssrcInfo;
}

}  // namespace ZLM