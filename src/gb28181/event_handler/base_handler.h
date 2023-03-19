/*
**	********************************************************************************
**
**	File		: base_handler.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <osipparser2/osip_message.h>


namespace GB28181 {


/**
 * @brief 事件处理接口基类
 *  
 */
class BaseHandler
{
public:
    BaseHandler() = default;
    virtual ~BaseHandler() = default;

protected:

    /**
     * @brief 发送简单的响应
     * 
     * @param uname     用户名
     * @param excontext exosip上下文
     * @param tid       事务id
     * @param status    状态码
     * @return int 
     */
    int sendSimplyResp(const char* uname, struct eXosip_t* excontext, int tid, int status);

    /**
     * @brief 发送ACK
     * 
     * @param excontext exosip上下文
     * @param did       事务id
     * @return int 
     */
    int sendCallAck(struct eXosip_t *excontext, int did);

    /**
     * @brief 从响应中获取状态码
     * 
     * @param resp 响应
     * @return int 
     */
    int getStatcodeFromResp(osip_message_t* resp);

    /**
     * @brief 从请求中获取消息id
     * 
     * @param req 请求
     * @return const char* 
     */
    const char* getMsgIdFromReq(osip_message_t* req);
};

}
