/*
**	********************************************************************************
**
**	File		: requested_pool.cpp
**	Description	:
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/

#include "requested_pool.h"
#include "Poller/EventPoller.h"
#include "Poller/Timer.h"
#include "Util/logger.h"

namespace GB28181 {

// RequestedPool *RequestedPool::instance() {
//     static RequestedPool _ins;
//     return &_ins;
// }

int RequestedPool::Init() {
    check_requet_timeout(60);
    return 0;
}

bool RequestedPool::AddRequest(string &reqid, BaseRequest::ptr req) {
    lock_guard<mutex> guard(m_mutex);
    if (m_requestmap.find(reqid) != m_requestmap.end()) {
        WarnL << "[RequestedPool] AddRequest: " << reqid << " already added.";
        return false;
    }
    InfoL << "[RequestedPool] AddRequest: " << reqid << " success.";
    req->SetReqid(reqid);
    m_requestmap[reqid] = req;
    return false;
}

bool RequestedPool::DelRequest(string &reqid) {
    lock_guard<mutex> guard(m_mutex);
    auto              req = m_requestmap.find(reqid);
    if (req != m_requestmap.end()) {
        m_requestmap.erase(req);
        InfoL << "delete request: " << reqid << " success.";
        return true;
    }
    InfoL << "delete request: " << reqid << " failed.";
    return false;
}

MessageRequest::ptr RequestedPool::GetMsgRequestBySn(const string &reqsn) {
    lock_guard<mutex> guard(m_mutex);
    for (auto &req : m_requestmap) {
        MessageRequest::ptr msgreq = dynamic_pointer_cast<MessageRequest>(req.second);
        if (msgreq->GetReqSn() == reqsn) {
            return msgreq;
        }
    }
    return nullptr;
}

int RequestedPool::HandleMsgResponse(string &reqid, int status_code) {
    return handle_response(reqid, status_code);
}

//
int RequestedPool::check_requet_timeout(double timeout) {
    check_requet_timeout_timer.reset(new toolkit::Timer(
        10,
        [this,timeout]() {
            // InfoL << "定期请求超时检查和清理";
            time_t            now = time(nullptr);
            lock_guard<mutex> guard(m_mutex);
            for (auto itr = m_requestmap.begin(); itr != m_requestmap.end();) {
                if (now - itr->second->GetReqtime() > timeout) {
                    // 如果这个请求不是完成状态，说明这个请求从发出到超时时间内都没有收到回复或者没有被内部处理
                    if (!itr->second->IsFinished()) {
                        itr->second->HandleResponse(-1);  // 先暂定-1的错误码为完全超时
                        itr->second->finished();
                    }
                    itr = m_requestmap.erase(itr);
                } else {
                    ++itr;
                }
            }
            return true;
        },
        nullptr)
    );
    return 0;
}

int RequestedPool::handle_response(string &reqid, int status_code) {
    // 从请求池中找到对应请求，触发回调
    BaseRequest::ptr req;
    {
        lock_guard<mutex> guard(m_mutex);
        auto              itr = m_requestmap.find(reqid);
        if (itr == m_requestmap.end()) {
            WarnL << "handle_response: " << reqid << " not found 有可能是超时被清理";
            return -1;
        }
        req = itr->second;
        // 收到请求回复后不移除请求了，在定时器中检测后清理
    }

    toolkit::EventPollerPool::Instance().getExecutor()->async([req, status_code]() {
            req->HandleResponse(status_code);
    });

    return 0;
}

}  // namespace GB28181
