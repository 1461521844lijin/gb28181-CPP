/*
**	********************************************************************************
**
**	File		: request_manager.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/

#include <glog/logging.h>
#include "request_manager.h"

namespace GB28181 {

extern const char* request_type_str[OUTCOMING_REQ_TYPE_MAX];

RequestManager *RequestManager::instance()
{
    static RequestManager _ins;
    return &_ins;
}

int RequestManager::Start()
{
    task = std::thread(&RequestManager::check_requet_timeout, this);
    // Infra::ThreadTask task = bind(&RequestManager::check_requet_timeout, this);
    // Infra::CThreadPool::instance()->run(task);
    return 0;
}

int RequestManager::AddRequest(string &reqid, BaseRequest::ptr &req)
{
    outcoming_req_type_e reqtype = req->GetReqType();
    base_request_map_t* p_reqmap = get_base_request_map(reqtype);
    if (p_reqmap == nullptr) {
        LOG(WARNING) << "[RequestManager] AddRequest: " << request_type_str[reqtype] <<
        ", reqid: " << reqid << " failed, no this request type in center.";
        return -1;
    }

    lock_guard<mutex> guard(p_reqmap->m);
    if (p_reqmap->req_map.find(reqid) != p_reqmap->req_map.end()) {
        LOG(WARNING) << "[RequestManager] AddRequest: " << request_type_str[reqtype] <<
                 ", reqid: " << reqid << " already added.";
        return -2;
    }
    req->SetReqid(reqid);
    p_reqmap->req_map[reqid] = req;

    LOG(WARNING) << "[RequestManager] AddRequest: " << request_type_str[reqtype] <<
             ", reqid: " << reqid << " added success.";

    return 0;
}

int RequestManager::DelRequest(outcoming_req_type_e reqtype, string &reqid)
{
    base_request_map_t* p_reqmap = get_base_request_map(reqtype);
    if (nullptr == p_reqmap) {
        return -1;
    }

    lock_guard<mutex> guard(p_reqmap->m);
    if (p_reqmap->req_map.find(reqid) == p_reqmap->req_map.end()) {
        LOG(WARNING) << "delete request: " << request_type_str[reqtype] << ", reqid: "<< reqid << " does not exist.";
        return -2;
    }

    p_reqmap->req_map.erase(reqid);
    LOG(WARNING) << "delete request: " << request_type_str[reqtype] << ", reqid: "<<reqid << " success.";
    return 0;
}

int RequestManager::GetMsgRequestBySn(const string &reqsn, MessageRequestSptr& msgreq)
{
    lock_guard<mutex> guard(m_messagemap.m);
    BaseRequestMap::const_iterator itr;
    for (; itr != m_messagemap.req_map.end(); ++itr) {
        msgreq = dynamic_pointer_cast<MessageRequest>(itr->second);
        if (msgreq->GetReqSn() == reqsn) {
            return 0;
        }
    }
    return -1;
}

int RequestManager::HandleMsgResponse(string &reqid, int status_code)
{
    return handle_response(m_messagemap, reqid, status_code);
}


// todo 后期改为事件触发形式  不再以线程轮询的方式
int RequestManager::check_requet_timeout()
{
    /// 超时时间 6s
    int timeout = 6;
    base_request_map_t* p_reqmap[] = {&m_messagemap,};
    int p_size = sizeof(p_reqmap) / sizeof(base_request_map_t*);

    time_t now = time(nullptr);
    for (int i=0; i < p_size; ++i) {
        base_request_map_t* reqmap = p_reqmap[i];
        lock_guard<mutex> guard(reqmap->m);

        auto itr = reqmap->req_map.begin();
        for (; itr != reqmap->req_map.end();) {
            //  超时处理
            if (now - itr->second->GetReqtime() > timeout) {
                itr->second->HandleResponse(-1);
                LOG(INFO) << "check_request_timeout: " << request_type_str[itr->second->GetReqType()] << " timeout";
                itr = reqmap->req_map.erase(itr);
            }
            else {
                ++itr;
            }
        }
    }
    return 0;
}

base_request_map_t * RequestManager::get_base_request_map(outcoming_req_type_e requtype)
{
    switch (requtype)
    {
        case OUTCOMING_REQU_TYPE_KEEPALIVE:
            return &m_messagemap;

        default:
            return nullptr;
    }
}

int RequestManager::handle_response(base_request_map_t &reqmap, string &reqid, int status_code)
{
    if (reqid.length() <1) {
        return 0;
    }
    lock_guard<mutex> guard(reqmap.m);
    auto itr = reqmap.req_map.find(reqid);
    if (itr == reqmap.req_map.end()) {
        LOG(INFO) << "handle_response: " << reqid <<" does not exist, it doesn't need to be handled!";
        return 0;
    }

    switch (itr->second->GetReqType())
    {
        //TODO
        case OUTCOMING_REQU_TYPE_KEEPALIVE:
            itr->second->HandleResponse(status_code);
            break;
        default:
            return -1;
    }

    // 如果在处理响应的过程中，请求已经完成，那么就从请求中心删除该请求
    if (itr->second->IsFinished()) {
        reqmap.req_map.erase(reqid);
        LOG(INFO) << "handel_response: " << request_type_str[itr->second->GetReqType()] << ", reqid: "
                    << reqid << " finished, delete from request center.";
    }
    return 0;
}

}
