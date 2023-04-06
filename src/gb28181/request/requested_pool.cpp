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
#include <glog/logging.h>

namespace GB28181 {

// RequestedPool *RequestedPool::instance() {
//     static RequestedPool _ins;
//     return &_ins;
// }

int RequestedPool::Init() {
    
    check_requet_timeout();
    return 0;
}

bool RequestedPool::AddRequest(string &reqid, BaseRequest::ptr req) {
    lock_guard<mutex> guard(m_mutex);
    if (m_requestmap.find(reqid) != m_requestmap.end()) {
        LOG(WARNING) << "[RequestedPool] AddRequest: " << reqid << " already added.";
        return false;
    }
    LOG(INFO) << "[RequestedPool] AddRequest: " << reqid << " success.";
    req->SetReqid(reqid);
    m_requestmap[reqid] = req;
    return false;
}

bool RequestedPool::DelRequest(REQ_MESSAGE_TYPE reqtype, string &reqid) {
    lock_guard<mutex> guard(m_mutex);
    auto              req = m_requestmap.find(reqid);
    if (req != m_requestmap.end()) {
        m_requestmap.erase(req);
        LOG(INFO) << "delete request: " << reqid << " success."
                  << "type: " << req->second->GetReqType();
        return true;
    }
    LOG(INFO) << "delete request: " << reqid << " failed."
              << "type: " << req->second->GetReqType();
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
        timeout,
        [this]() {
            LOG(INFO) << "定期请求超时检查和清理";
            time_t            now = time(nullptr);
            lock_guard<mutex> guard(m_mutex);
            for (auto itr = m_requestmap.begin(); itr != m_requestmap.end();) {
                //  异步 超时处理
                if (now - itr->second->GetReqtime() > 6) {
                    itr->second->HandleResponse(-1);
                    LOG(INFO) << "check_request_timeout_type: " << itr->second->GetReqType()
                                  << " " << itr->first;
                    itr->second->finished();
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
            LOG(WARNING) << "handle_response: " << reqid << " not found 有可能是超时被清理";
            return -1;
        }
        req = itr->second;
        // m_requestmap.erase(itr);
    }

    // 异步执行请求错误的回调  回调中需要唤醒阻塞请求;
    if(status_code != 200){
        toolkit::EventPollerPool::Instance().getExecutor()->async([req, status_code]() {
            req->HandleResponse(status_code);
            req->finished();
        });
    }

    return 0;
}

}  // namespace GB28181
