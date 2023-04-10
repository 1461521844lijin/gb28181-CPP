#include "ssrc_config.h"

#include <algorithm>
#include <memory>

namespace ZLM {

// 播流最大并发数
#define MAX_STRTEAM_COUNT 10000

int SSRCInfo::getPort() const {
    return m_port;
}

void SSRCInfo::setPort(int port) {
    m_port = port;
}

const std::string &SSRCInfo::getSsrc() const {
    return m_ssrc;
}

void SSRCInfo::setSsrc(const std::string &ssrc) {
    m_ssrc = ssrc;
}

const std::string &SSRCInfo::getStrema() const {
    return m_strema;
}

void SSRCInfo::setStrema(const std::string &strema) {
    m_strema = strema;
}

SSRCConfig::SSRCConfig(const std::string        &mediaServerId,
                       const std::string        &sipDomain) {
    m_mediaServerId = mediaServerId;
    m_ssrcIsUsed.resize(MAX_STRTEAM_COUNT);
    m_ssrcUnused.resize(MAX_STRTEAM_COUNT);
    m_ssrcPrefix = sipDomain.substr(3, 8);

    for (int i = 0; i < MAX_STRTEAM_COUNT; i++) {
        std::string ssrc;
        if (i < 10) {
            ssrc = "000" + std::to_string(i);
        } else if (i < 100) {
            ssrc = "00" + std::to_string(i);
        } else if (i < 1000) {
            ssrc = "0" + std::to_string(i);
        } else {
            ssrc = std::to_string(i);
        }
        m_ssrcIsUsed.push_back(ssrc);        
    }
}

std::string SSRCConfig::getSsrcPrefix() const {
    return m_ssrcPrefix;
}

void SSRCConfig::setSsrcPrefix(const std::string &ssrcPrefix) {
    m_ssrcPrefix = ssrcPrefix;
}

std::string SSRCConfig::getMediaServerId() const {
    return m_mediaServerId;
}

void SSRCConfig::setMediaServerId(const std::string &mediaServerId) {
    m_mediaServerId = mediaServerId;
}

bool SSRCConfig::checkSsrc(const std::string &ssrc) {
    if (ssrc.empty()) {
        return false;
    }
    std::string sn = ssrc.substr(6);
    if (std::find(m_ssrcIsUsed.begin(), m_ssrcIsUsed.end(), sn) == m_ssrcIsUsed.end()) {
        return true;
    }
    return false;
}

std::string SSRCConfig::getSN() {
    std::string sn    = "";
    int         index = 0;
    if (m_ssrcUnused.size() == 0) {
        throw std::runtime_error("ssrc is not enough");
    } else if (m_ssrcUnused.size() == 1) {
        sn = m_ssrcUnused.front();
    } else {
        index = rand() % m_ssrcUnused.size();
        sn    = m_ssrcUnused[index];
    }

    m_ssrcIsUsed.push_back(sn);
    m_ssrcUnused.erase(m_ssrcUnused.begin() + index);

    return sn;
}

std::string SSRCConfig::getPlaySsrc() {
    std::string ssrc = "0" + m_ssrcPrefix + getSN();
    return ssrc;
}

std::string SSRCConfig::getPlayBackSsrc() {
    std::string ssrc = "1" + m_ssrcPrefix + getSN();
    return ssrc;
}

void SSRCConfig::releaseSsrc(const std::string &ssrc) {
    if (ssrc.empty()) {
        return;
    }
    std::string                        sn = ssrc.substr(6);
    std::vector<std::string>::iterator it =
        std::find(m_ssrcIsUsed.begin(), m_ssrcIsUsed.end(), ssrc);
    if (it != m_ssrcIsUsed.end()) {
        m_ssrcUnused.push_back(ssrc);
        m_ssrcIsUsed.erase(it);
    }
}

}  // namespace ZLM
