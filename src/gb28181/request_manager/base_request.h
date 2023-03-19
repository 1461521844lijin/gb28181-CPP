/*
**	********************************************************************************
**
**	File		: base_request.h
**	Description	:
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include "defs.h"
#include <condition_variable>
#include <map>
#include <memory>
using namespace std;

namespace GB28181 {

class BaseRequest {
public:
    typedef std::shared_ptr<BaseRequest> ptr;
    explicit BaseRequest(outcoming_req_type_e reqtype);
    virtual ~BaseRequest();

    /// @brief 请求响应接口 虚函数被子类重写
    virtual int HandleResponse(int statcode);

    // 设置是否等待
    void SetWait(bool bwait);

    /// 等待请求完成
    void WaitResult();

    /// 请求是否完成
    bool IsFinished();

    /// 设置请求ID
    int SetReqid(string &id);

    /// @brief 获取请求类型
    /// @return 请求类型
    outcoming_req_type_e GetReqType();

    /// @brief 获取请求时间
    time_t GetReqtime();

protected:
    /// @brief 请求完成 会唤醒等待的请求
    int onRequestFinished();

private:
    /// @brief 请求完成
    void finished();

protected:
    string m_reqid;  ///< 请求ID

private:
    bool                 m_bfinished;  ///< 请求是否完成
    bool                 m_bwait;      ///< 是否等待请求完成
    time_t               m_reqtime;    ///< 请求时间
    outcoming_req_type_e m_reqtype;    ///< 请求类型
    mutex                m_mutex;
    condition_variable   m_cond;
};

typedef map<string, BaseRequest::ptr> BaseRequestMap;  ///< 请求ID, 请求对象

struct base_request_map_t {
    mutex          m;
    BaseRequestMap req_map;
};

}  // namespace GB28181
