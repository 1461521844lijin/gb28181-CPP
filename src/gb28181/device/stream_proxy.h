#pragma once

#include "utils/Singleton.h"
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
namespace GB28181 {

class StreamProxy {
public:
    typedef std::shared_ptr<StreamProxy> ptr;
    StreamProxy() = delete;
    StreamProxy(const std::string &mediaServerId,
                const std::string &app,
                const std::string &streamId);

private:
    std::mutex              m_mutex;
    std::condition_variable m_cond;

    std::string m_mediaServerId;
    std::string m_app;
    std::string m_streamId;

public:
    void        setMediaServerId(const std::string &mediaServerId);
    std::string getMediaServerId();
    void        setApp(const std::string &app);
    std::string getApp();
    void        setStreamId(const std::string &streamId);
    std::string getStreamId();
};

class StreamProxyManager {
public:
    typedef std::shared_ptr<StreamProxyManager> ptr;
    StreamProxyManager()  = default;
    ~StreamProxyManager() = default;

private:
    std::mutex m_mutex;
    // mediaServerId -> streamId -> streamProxy
    std::map<std::string, std::map<std::string, StreamProxy::ptr>> m_streamProxy_map;

public:
    void addStreamProxy(StreamProxy::ptr streamProxy);
    void removeStreamProxy(const std::string &mediaServerId, const std::string &streamId);

    StreamProxy::ptr getStreamProxy(const std::string &mediaServerId, const std::string &streamId);
    std::map<std::string, StreamProxy::ptr> getStreamProxy(const std::string &mediaServerId);
    std::map<std::string, std::map<std::string, StreamProxy::ptr>> getStreamProxy();

    void clearStreamProxy(const std::string &mediaServerId);
};

typedef Tools::Singleton<StreamProxyManager> g_StreamProxyMgr;

}  // namespace GB28181
