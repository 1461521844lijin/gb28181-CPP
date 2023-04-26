#pragma once

#include "utils/Singleton.h"
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>

#include "zlmedia/zlmedia_server/zlm_server.hpp"

namespace GB28181 {

enum STREAM_TYPE {
    STREAM_TYPE_NONE = 0,
    STREAM_TYPE_GB   = 1,
    STREAM_TYPE_PROXY = 2,
    STREAM_TYPE_PUSH = 3,
    STREAM_TYPE_MAX
};

class BaseStream {
public:
    typedef std::shared_ptr<BaseStream> ptr;
    BaseStream() = delete;
    BaseStream(ZLM::ZlmServer::ptr mediaServer,
               const std::string  &app,
               const std::string  &streamId,
               STREAM_TYPE         type);
    virtual ~BaseStream() = default;

protected:
    std::mutex              m_mutex;
    std::condition_variable m_cond;

    ZLM::ZlmServer::ptr m_mediaServer;
    std::string         m_app;
    std::string         m_streamId;
    STREAM_TYPE         m_type;

public:
    void                setMediaServer(ZLM::ZlmServer::ptr mediaServer);
    ZLM::ZlmServer::ptr getMediaServer();
    void                setApp(const std::string &app);
    std::string         getApp();
    void                setStreamId(const std::string &streamId);
    std::string         getStreamId();
    void                setType(STREAM_TYPE type);
    STREAM_TYPE         getType();
};

class StreamManager {
public:
    typedef std::shared_ptr<StreamManager> ptr;
    StreamManager()  = default;
    ~StreamManager() = default;

private:
    std::mutex m_mutex;
    // streamId -> stream
    std::map<std::string, BaseStream::ptr> m_stream_map;

public:
    void addStream(BaseStream::ptr stream);
    void removeStream(const std::string &streamId);

    BaseStream::ptr                        getStream(const std::string &streamId);
    std::map<std::string, BaseStream::ptr> getStream();
    std::vector<BaseStream::ptr>           getStreamByType(STREAM_TYPE type);


    BaseStream::ptr makeStream(const std::string& mediaServerid, const std::string &streamId, const std::string &app ,STREAM_TYPE type);

    void clearStream();
};

typedef Tools::Singleton<StreamManager> g_StreamMgr;

}  // namespace GB28181
