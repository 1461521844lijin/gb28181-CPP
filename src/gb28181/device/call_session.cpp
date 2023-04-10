#include "call_session.h"

namespace GB28181 {

CallSession::CallSession(const std::string &mediaServerId, const ZLM::SSRCInfo::ptr &ssrc) {
    m_mediaServerId = mediaServerId;
    m_ssrcInfo      = ssrc;
}

void CallSession::setMediaServerId(const std::string &mediaServerId) {
    m_mediaServerId = mediaServerId;
}

std::string CallSession::getMediaServerId() {
    return m_mediaServerId;
}

void CallSession::setSsrc(const ZLM::SSRCInfo::ptr &ssrc) {
    m_ssrcInfo = ssrc;
}

ZLM::SSRCInfo::ptr CallSession::getSsrc() {
    return m_ssrcInfo;
}

void CallSession::setConnected(bool isConnected) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_isConnected = isConnected;
}

bool CallSession::isConnected() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_isConnected;
}

void CallSession::addStream(const std::string &streamId,
                            const std::string &app,
                            const std::string &schema) {
    std::unique_lock<std::mutex> lock(m_mutex);
    streaminfo                   info;
    info.app          = app;
    info.streamId     = streamId;
    info.schema       = schema;
    m_streams[schema] = info;
}

void CallSession::removeStream(const std::string &schema) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_streams.erase(schema);
}

std::map<std::string, CallSession::streaminfo> CallSession::getStreams() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_streams;
}

int CallSession::getCallId() const {
    return m_callId;
}

void CallSession::setCallId(int callId) {
    m_callId = callId;
}

int CallSession::getDialogId() const {
    return m_dialogId;
}

void CallSession::setDialogId(int dialogId) {
    m_dialogId = dialogId;
}

void CallSessionManager::addCallSession(const std::string &deviceId, CallSession::ptr callSession) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_callSession_map[deviceId] = callSession;
}

CallSession::ptr CallSessionManager::getCallSession(const std::string &deviceId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto                         it = m_callSession_map.find(deviceId);
    if (it != m_callSession_map.end()) {
        return it->second;
    }
    return nullptr;
}

void CallSessionManager::removeCallSession(const std::string &deviceId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_callSession_map.erase(deviceId);
}

void CallSessionManager::removeCallSessionByMediaServerId(const std::string &mediaServerId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    for (auto it = m_callSession_map.begin(); it != m_callSession_map.end();) {
        if (it->second->getMediaServerId() == mediaServerId) {
            it = m_callSession_map.erase(it);
        } else {
            ++it;
        }
    }
}

}  // namespace GB28181