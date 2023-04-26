#include "call_session.h"

namespace GB28181 {

bool CallSession::wait_for_stream_ready() {
    std::unique_lock<std::mutex> lock(m_mutex);
    auto                         status = m_cond.wait_for(lock, std::chrono::seconds(6));
    if (status == std::cv_status::timeout) {
        return false;
    }
    return true;
}

void CallSession::notify_stream_ready() {
    m_cond.notify_all();
}

CallSession::CallSession(ZLM::ZlmServer::ptr       mediaServer,
                         const ZLM::SSRCInfo::ptr &ssrc,
                         const std::string        &app,
                         const std::string        &streamId,
                         STREAM_TYPE               type)
    : BaseStream(mediaServer, app, streamId, type), m_ssrcInfo(ssrc) {}

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

}  // namespace GB28181