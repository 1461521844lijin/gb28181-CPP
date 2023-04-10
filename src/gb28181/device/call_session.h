#pragma once

#include "utils/Singleton.h"
#include "zlmedia/zlmedia_server/ssrc_config.h"
#include <map>
#include <memory>
#include <mutex>

namespace GB28181 {

class CallSession {
public:
    typedef std::shared_ptr<CallSession> ptr;

public:
    struct streaminfo {
        std::string app, streamId, schema;
    };

private:
    bool       m_isConnected = false;
    std::mutex m_mutex;

    std::map<std::string, streaminfo> m_streams;  // schema -> streaminfo
    std::string                       m_mediaServerId;
    ZLM::SSRCInfo::ptr                m_ssrcInfo;
    int                               m_callId;    // 设备呼叫id
    int                               m_dialogId;  // 设备对话id

public:
    CallSession(const std::string &mediaServerId, const ZLM::SSRCInfo::ptr &ssrc);
    ~CallSession() = default;

    int                getCallId() const;
    void               setCallId(int callId);
    int                getDialogId() const;
    void               setDialogId(int dialogId);
    void               setMediaServerId(const std::string &mediaServerId);
    std::string        getMediaServerId();
    void               setSsrc(const ZLM::SSRCInfo::ptr &ssrc);
    ZLM::SSRCInfo::ptr getSsrc();
    void               setConnected(bool isConnected);
    bool               isConnected();
    void addStream(const std::string &streamId, const std::string &app, const std::string &schema);
    void removeStream(const std::string &schema);
    std::map<std::string, streaminfo> getStreams();
};

class CallSessionManager {
private:
    std::mutex m_mutex;
    // 设备id -> 呼叫会话对象
    std::map<std::string, CallSession::ptr> m_callSession_map;

public:
    CallSessionManager()  = default;
    ~CallSessionManager() = default;

    void             addCallSession(const std::string &deviceId, CallSession::ptr callSession);
    CallSession::ptr getCallSession(const std::string &deviceId);
    void             removeCallSession(const std::string &deviceId);
    void             removeCallSessionByMediaServerId(const std::string &mediaServerId);
};

typedef Tools::Singleton<CallSessionManager> g_CallSessionMgr;

}  // namespace GB28181
