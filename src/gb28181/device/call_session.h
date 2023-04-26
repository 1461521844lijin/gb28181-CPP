#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <condition_variable>

#include "utils/Singleton.h"
#include "zlmedia/zlmedia_server/ssrc_config.h"
#include "base_stream.h"

namespace GB28181 {

class CallSession : public BaseStream
{
public:
    typedef std::shared_ptr<CallSession> ptr;

private:
    bool       m_isConnected = false;

    ZLM::SSRCInfo::ptr                m_ssrcInfo;
    int                               m_callId;    // 设备呼叫id
    int                               m_dialogId;  // 设备对话id

public:
    CallSession(ZLM::ZlmServer::ptr mediaServer, 
                const ZLM::SSRCInfo::ptr &ssrc, 
                const std::string &app, 
                const std::string &streamId, 
                STREAM_TYPE type = STREAM_TYPE_GB);
    ~CallSession() = default;

    int                getCallId() const;
    void               setCallId(int callId);
    int                getDialogId() const;
    void               setDialogId(int dialogId);
    void               setSsrc(const ZLM::SSRCInfo::ptr &ssrc);
    ZLM::SSRCInfo::ptr getSsrc();
    void               setConnected(bool isConnected);
    bool               isConnected();

    bool wait_for_stream_ready();
    void notify_stream_ready();
};

}  // namespace GB28181
