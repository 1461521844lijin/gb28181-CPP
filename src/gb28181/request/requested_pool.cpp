/*
**	********************************************************************************
**
**	File		: requested_pool.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/

#include <glog/logging.h>
#include "requested_pool.h"

namespace GB28181 {

// extern const char* request_type_str[OUTCOMING_REQ_TYPE_MAX];

RequestedPool *RequestedPool::instance()
{
    static RequestedPool _ins;
    return &_ins;
}

int RequestedPool::Init()
{
    // TODO 需要有定时任务去轮询请求是否超时



    // task = std::thread(&RequestedPool::check_requet_timeout, this);
    // Infra::ThreadTask task = bind(&RequestedPool::check_requet_timeout, this);
    // Infra::CThreadPool::instance()->run(task);
    return 0;
}

bool RequestedPool::AddRequest(string &reqid, BaseRequest::ptr req)
{

    lock_guard<mutex> guard(m_mutex);
    if(m_requestmap.find(reqid) != m_requestmap.end()) {
        LOG(WARNING) << "[RequestedPool] AddRequest: " << reqid << " already added.";
        return false;
    }

    req->SetReqid(reqid);
    m_requestmap[reqid] = req;
    return false;
}

bool RequestedPool::DelRequest(REQ_MESSAGE_TYPE reqtype, string &reqid)
{
    
    lock_guard<mutex> guard(m_mutex);
    auto req = m_requestmap.find(reqid);
    if(req != m_requestmap.end()) {
        m_requestmap.erase(req);
        LOG(INFO) << "delete request: " << reqid << " success."<< "type: " << req->second->GetReqType();
        return true;
    }
    LOG(INFO) << "delete request: " << reqid << " failed."<< "type: " << req->second->GetReqType();
    return false;
}

MessageRequest::ptr RequestedPool::GetMsgRequestBySn(const string &reqsn)
{
    lock_guard<mutex> guard(m_mutex);
    for (auto &req : m_requestmap) {
        MessageRequest::ptr msgreq = dynamic_pointer_cast<MessageRequest>(req.second);
        if (msgreq->GetReqSn() == reqsn) {
            return msgreq;
        }
    }
    return nullptr;
}

int RequestedPool::HandleMsgResponse(string &reqid, int status_code)
{
    return handle_response(reqid, status_code);
}


// todo 后期改为事件触发形式  不再以线程轮询的方式
int RequestedPool::check_requet_timeout()
{
    // /// 超时时间 6s
    // int timeout = 6;
    // base_request_map_t* p_reqmap[] = {&m_messagemap,};
    // int p_size = sizeof(p_reqmap) / sizeof(base_request_map_t*);

    // time_t now = time(nullptr);
    // for (int i=0; i < p_size; ++i) {
    //     base_request_map_t* reqmap = p_reqmap[i];
    //     lock_guard<mutex> guard(reqmap->m);

    //     auto itr = reqmap->req_map.begin();
    //     for (; itr != reqmap->req_map.end();) {
    //         //  超时处理
    //         if (now - itr->second->GetReqtime() > timeout) {
    //             itr->second->HandleResponse(-1);
    //             // LOG(INFO) << "check_request_timeout: " << request_type_str[itr->second->GetReqType()] << " timeout";
    //             itr = reqmap->req_map.erase(itr);
    //         }
    //         else {
    //             ++itr;
    //         }
    //     }
    // }
    return 0;
}


int RequestedPool::handle_response(string &reqid, int status_code)
{
    // 请求完成，需要从请求管理中删除，同时触发回调或者唤醒阻塞的请求
    // TODO   异步触发回到或者唤醒阻塞的请求

    BaseRequest::ptr req;
    {
        lock_guard<mutex> guard(m_mutex);
        auto itr = m_requestmap.find(reqid);
        if (itr == m_requestmap.end()) {
            LOG(WARNING) << "handle_response: " << reqid << " not found 有可能是超时被清理";
            return -1;
        }
        req = itr->second;
        m_requestmap.erase(itr);
    }


    // TODO 异步执行回调  回调中需要唤醒阻塞请求;
    req->HandleResponse(status_code);

    return 0;
}

}
