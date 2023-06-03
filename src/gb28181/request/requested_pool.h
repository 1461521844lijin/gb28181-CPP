/*
**	********************************************************************************
**
**	File		: requested_pool.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include "base_request.h"
#include "base_request.h"
#include <thread>
#include "utils/Singleton.h"
#include <map>
#include <mutex>
#include "Poller/Timer.h"
using namespace std;

namespace GB28181 {


///< 请求管理类   
///< 用于管理所有请求  TODO  需要有定时任务去轮询请求是否超时
class RequestedPool
{
public:
    // RequestedPool() = default;
    // ~RequestedPool() = default;

    // static RequestedPool * instance();

    int Init();

    /**
     * @brief 添加请求
     * 
     * @param reqid 请求ID
     * @param req 请求对象
     * 
     * @return 0 成功 -1 未定义该类请求 -2 已存在该请求
     */
    bool AddRequest(string& reqid, BaseRequest::ptr req);

    /**
     * @brief 删除请求
     *
     * @param reqtype 请求类型
     * @param reqid 请求ID
     *
     * @return true
     */
    bool DelRequest(string &reqid);

    /**
     * @brief 根据请求SN（序列号）和类型，获取请求对象  这个方法性能比较差，需要优化
     * 
     * @param reqsn 请求SN
     * @return req 返回请求对象
     */
    MessageRequest::ptr GetMsgRequestBySn(const string& reqsn);

    int HandleMsgResponse(string& reqid, int status_code);

private:

    /**
     * @brief 启动一个定时器，处理超时请求，默认超时时间6秒
     */
    int check_requet_timeout(double timeout);


    /// @brief 请求相应处理函数
    /// @param reqmap 
    /// @param reqid 
    /// @param status_code 
    /// @return 
    int handle_response(string& reqid, int status_code);

private:

    std::map<string, BaseRequest::ptr> m_requestmap; // 请求map <id,req>
    std::mutex m_mutex;
    toolkit::Timer::Ptr check_requet_timeout_timer;
};

typedef Tools::Singleton<RequestedPool> g_RequestedPool;


}

