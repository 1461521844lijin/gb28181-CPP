#include "zlm_server.hpp"

#include "application/dto/api/StreamInfoDto.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "utils/httplib.h"
#include "utils/url_code.h"
#include "zlmedia/dto/open_rtp_server_dto.hpp"
#include <strstream>

#include "Util/logger.h"

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
    InfoL << "openRTPServer path: " << path;
    try {
        auto res = cli.Post(path.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto res_obj =
                json_Mapper->readFromString<oatpp::Object<DTO::ZLM::openRtpServerRes>>(res->body);
            if (res_obj->code == 0) {
                port = res_obj->port;
            } else {
                ErrorL << "openRTPServer failed: " << *res_obj->msg;
                return nullptr;
            }
        }
        if (port == 0) {
            ErrorL << "openRTPServer failed,"
                   << " httperr " << res.error();
            return nullptr;
        }
    } catch (const std::exception &e) {
        ErrorL << "openRTPServer failed: " << e.what();
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

std::string ZlmServer::getMp4RecordFile(const std::string &app,
                                        const std::string &streamid,
                                        const std::string &period) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::string     path = "/index/api/getMp4RecordFile?secret=" + m_zlm_secret +
                       "&vhost=__defaultVhost__" + "&app=" + app + "&stream=" + streamid +
                       "&period=" + period;
    InfoL << "getMp4RecordFile path: " << path;
    try {
        auto res = cli.Post(path.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            return body;
        }
        ErrorL << "getMp4RecordFile failed,"
               << " httperr " << res.error();
        return "";
    } catch (const std::exception &e) {
        ErrorL << "getMp4RecordFile failed: " << e.what();
        return "";
    }
}

std::string ZlmServer::startRecordMp4(const std::string &app,
                                      const std::string &streamid,
                                      const int          maxSecond) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    // 范例：http://127.0.0.1/index/api/startRecord?type=1&vhost=__defaultVhost__&app=live&stream=obs
    std::string path = "/index/api/startRecord?secret=" + m_zlm_secret +
                       "&type=1&vhost=__defaultVhost__" + "&app=" + app + "&stream=" + streamid +
                       "&maxSecond=" + std::to_string(maxSecond);
    InfoL << "startRecordMp4 path: " << path;
    try {
        auto res = cli.Get(path.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            return body;
        }
        ErrorL << "startRecordMp4 failed,"
               << " httperr " << res.error();
        return "";
    } catch (const std::exception &e) {
        ErrorL << "startRecordMp4 failed: " << e.what();
        return "";
    }
}

std::string ZlmServer::stopRecordMp4(const std::string &app, const std::string &streamid) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::string     path = "/index/api/stopRecord?secret=" + m_zlm_secret +
                       "&type=1&vhost=__defaultVhost__" + "&app=" + app + "&stream=" + streamid;
    InfoL << "stopRecordMp4 path: " << path;
    try {
        auto res = cli.Get(path.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            return body;
        }
        ErrorL << "stopRecordMp4 failed,"
               << " httperr " << res.error();
        return "";
    } catch (const std::exception &e) {
        ErrorL << "stopRecordMp4 failed: " << e.what();
        return "";
    }
}

std::string ZlmServer::getRecordStatus(const std::string &app, const std::string &streamid) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::string     path = "/index/api/isRecording?secret=" + m_zlm_secret +
                       "&type=1&vhost=__defaultVhost__" + "&app=" + app + "&stream=" + streamid;
    InfoL << "getRecordStatus path: " << path;
    try {
        auto res = cli.Get(path.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            return body;
        }
        ErrorL << "getRecordStatus failed,"
               << " httperr " << res.error();
        return "";
    } catch (const std::exception &e) {
        ErrorL << "getRecordStatus failed: " << e.what();
        return "";
    }
}

std::string ZlmServer::getSnap(const std::string &url) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::strstream  ss;
    ss << "/index/api/getSnap?";
    ss << "secret=" << m_zlm_secret;
    ss << "&url=" << Tools::UrlEncode(url);
    ss << "&timeout_sec=10";
    ss << "&expire_sec=3";
    std::string path = ss.str();
    InfoL << "getSnap path: " << path;
    try {
        auto res = cli.Get(path.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            return body;
        }
        ErrorL << "getSnap failed,"
               << " httperr " << res.error();
        return "";
    } catch (const std::exception &e) {
        ErrorL << "getSnap failed: " << e.what();
        return "";
    }
}

// 设置录像流播放速度
std::string ZlmServer::setRecordSpeed(const std::string &path, const float &speed) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::strstream  ss;
    ss << "/index/api/setRecordSpeed?";
    ss << "secret=" << m_zlm_secret;
    ss << "&vhost=__defaultVhost__";
    ss << "&schema=rtsp";
    ss << "&app=record";
    ss << "&stream=" << path;
    ss << "&speed=" << std::to_string(speed);
    std::string paras = ss.str();
    InfoL << "setRecordSpeed path: " << paras;
    try {
        auto res = cli.Get(paras.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            return body;
        }
        ErrorL << "setRecordSpeed failed,"
               << " httperr " << res.error();
        return "";
    } catch (const std::exception &e) {
        ErrorL << "setRecordSpeed failed: " << e.what();
        return "";
    }
}

bool ZlmServer::addStreamProxy(const std::string &streamUrl,
                               const std::string &app,
                               const std::string &streamid) {
    std::string     addr = "http://" + m_zlm_addr + ":" + std::to_string(m_zlm_port);
    httplib::Client cli(addr);
    std::strstream  ss;
    ss << "/index/api/addStreamProxy?";
    ss << "secret=" << m_zlm_secret;
    ss << "&vhost=__defaultVhost__";
    ss << "&app=" << app;
    ss << "&stream=" << streamid;
    ss << "&url=" << Tools::UrlEncode(streamUrl);
    ss << "&rtp_type=0";
    ss << "&retry_count=0";
    // ss << "&timeout_sec=5";

    std::string paras = ss.str();
    InfoL << "addStreamProxy path: " << paras;
    try {
        auto res = cli.Get(paras.c_str());
        if (res.error() == httplib::Error::Success && res->status == 200) {
            std::string body = res->body;
            ErrorL << "\n" << body << "\n";
            auto json_Mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto res_obj =
                json_Mapper->readFromString<oatpp::Object<DTO::GETWAY::StreamProxyDto>>(body);
            // res_obj->data->key;
            if (res_obj->code == 0) {
                return true;
            } else {
                ErrorL << "addStreamProxy failed, msg: " << *res_obj->msg;
                return false;
            }
        }
        ErrorL << "addStreamProxy failed,"
               << " httperr " << res.error();
        return false;
    } catch (const std::exception &e) {
        ErrorL << "addStreamProxy failed: " << e.what();
        return false;
    }
}

}  // namespace ZLM