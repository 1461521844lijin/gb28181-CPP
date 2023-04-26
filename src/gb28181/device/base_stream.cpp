#include "base_stream.h"

#include "stream.h"
#include "zlmedia/zlmedia_server/zlm_manager.hpp"

namespace GB28181 {

BaseStream::BaseStream(ZLM::ZlmServer::ptr mediaServer,
                       const std::string  &app,
                       const std::string  &streamId,
                       STREAM_TYPE         type) {
    m_mediaServer = mediaServer;
    m_app         = app;
    m_streamId    = streamId;
    m_type        = type;
}

void BaseStream::setMediaServer(ZLM::ZlmServer::ptr mediaServer) {
    m_mediaServer = mediaServer;
}

ZLM::ZlmServer::ptr BaseStream::getMediaServer() {
    return m_mediaServer;
}

void BaseStream::setApp(const std::string &app) {
    m_app = app;
}

std::string BaseStream::getApp() {
    return m_app;
}

void BaseStream::setStreamId(const std::string &streamId) {
    m_streamId = streamId;
}

std::string BaseStream::getStreamId() {
    return m_streamId;
}

void BaseStream::setType(STREAM_TYPE type) {
    m_type = type;
}

STREAM_TYPE BaseStream::getType() {
    return m_type;
}

void StreamManager::addStream(BaseStream::ptr stream) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_stream_map[stream->getStreamId()] = stream;
}

void StreamManager::removeStream(const std::string &streamId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_stream_map.erase(streamId);
}

BaseStream::ptr StreamManager::getStream(const std::string &streamId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto                        it = m_stream_map.find(streamId);
    if (it != m_stream_map.end()) {
        return it->second;
    }
    return nullptr;
}

std::map<std::string, BaseStream::ptr> StreamManager::getStream() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_stream_map;
}

void StreamManager::clearStream() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_stream_map.clear();
}

BaseStream::ptr StreamManager::makeStream(const std::string &mediaServerid,
                                          const std::string &streamId,
                                          const std::string &app,
                                          STREAM_TYPE        type) {
    auto mediaServer = ZLM::g_ZlmMgr::GetInstance()->getZlmServer(mediaServerid);
    if (!mediaServer) {
        InfoL << "makeStream failed, mediaServerid:" << mediaServerid << " not exist";
        return nullptr;
    }
    BaseStream::ptr stream;
    switch (type) {
        case STREAM_TYPE::STREAM_TYPE_PUSH:
            stream = std::make_shared<StreamPushed>(mediaServer, app, streamId, type);
            break;
        case STREAM_TYPE::STREAM_TYPE_PROXY:
            stream = std::make_shared<StreamProxy>(mediaServer, app, streamId, type);
            break;
        default: break;
    }
    if (stream) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_stream_map[stream->getStreamId()] = stream;
    }
    return stream;
}

std::vector<BaseStream::ptr> StreamManager::getStreamByType(STREAM_TYPE type) {
    std::vector<BaseStream::ptr> streamList;
    std::lock_guard<std::mutex>  lock(m_mutex);
    for (auto &it : m_stream_map) {
        if (it.second->getType() == type) {
            streamList.push_back(it.second);
        }
    }
    return streamList;
}

}  // namespace GB28181
