/*
**	********************************************************************************
**
**	File		: request_manager.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include "base_request.h"
#include "message_request.h"
#include <thread>

using namespace std;

namespace GB28181 {

class RequestManager
{
public:
    RequestManager() = default;
    ~RequestManager() = default;

    static RequestManager * instance();

    int Start();

    /**
     * @brief 添加请求
     * 
     * @param reqid 请求ID
     * @param req 请求对象
     * 
     * @return 0 成功 -1 未定义该类请求 -2 已存在该请求
     */
    int AddRequest(string& reqid, BaseRequest::ptr& req);


    /**
     * @brief 删除请求
     * 
     * @param reqtype 请求类型
     * @param reqid 请求ID
     * 
     * @return 0 成功 -1 未定义该类请求 -2 不存在该请求
     */
    int DelRequest(outcoming_req_type_e reqtype, string& reqid);

    /**
     * @brief 根据请求SN（序列号）获取请求对象
     * 
     * @param reqsn 请求SN
     * @param msgreq 返回请求对象
     * 
     * @return 0 成功 -1 失败
     */
    int GetMsgRequestBySn(const string& reqsn, MessageRequestSptr& msgreq);

    int HandleMsgResponse(string& reqid, int status_code);

private:
    int check_requet_timeout();

    /**
     * @brief 根据请求类型获取请求对象map
     * 
     */
    base_request_map_t * get_base_request_map(outcoming_req_type_e requtype);

    /// @brief 请求相应处理函数
    /// @param reqmap 
    /// @param reqid 
    /// @param status_code 
    /// @return 
    int handle_response(base_request_map_t& reqmap, string& reqid, int status_code);

private:
    base_request_map_t m_messagemap;  // 消息请求map <id,req>
    std::thread         task;
};

}

