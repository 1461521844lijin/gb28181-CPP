#include "stream_proxy.h"

namespace GB28181 {

StreamProxy::StreamProxy(const std::string &mediaServerId,
                         const std::string &app,
                         const std::string &streamId) {
    m_mediaServerId = mediaServerId;
    m_app           = app;
    m_streamId      = streamId;
}

void StreamProxy::setMediaServerId(const std::string &mediaServerId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_mediaServerId = mediaServerId;
}

std::string StreamProxy::getMediaServerId() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_mediaServerId;
}

void StreamProxy::setApp(const std::string &app) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_app = app;
}

std::string StreamProxy::getApp() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_app;
}

void StreamProxy::setStreamId(const std::string &streamId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_streamId = streamId;
}

std::string StreamProxy::getStreamId() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_streamId;
}

void StreamProxyManager::addStreamProxy(StreamProxy::ptr streamProxy) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_streamProxy_map[streamProxy->getMediaServerId()][streamProxy->getStreamId()] = streamProxy;
}

void StreamProxyManager::removeStreamProxy(const std::string &mediaServerId,
                                           const std::string &streamId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_streamProxy_map[mediaServerId].erase(streamId);
}

StreamProxy::ptr StreamProxyManager::getStreamProxy(const std::string &mediaServerId,
                                                    const std::string &streamId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_streamProxy_map.find(mediaServerId) != m_streamProxy_map.end()) {
        if (m_streamProxy_map[mediaServerId].find(streamId) !=
            m_streamProxy_map[mediaServerId].end()) {
            return m_streamProxy_map[mediaServerId][streamId];
        }
    }
    return nullptr;
}

std::map<std::string, StreamProxy::ptr>
StreamProxyManager::getStreamProxy(const std::string &mediaServerId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_streamProxy_map.find(mediaServerId) != m_streamProxy_map.end()) {
        return m_streamProxy_map[mediaServerId];
    }
    return std::map<std::string, StreamProxy::ptr>();
}

std::map<std::string, std::map<std::string, StreamProxy::ptr>>
StreamProxyManager::getStreamProxy() {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_streamProxy_map;
}

void StreamProxyManager::clearStreamProxy(const std::string &mediaServerId) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_streamProxy_map.erase(mediaServerId);
}

}  // namespace GB28181
