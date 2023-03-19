/*
**	********************************************************************************
**
**	File		: sip_server.cpp
**	Description	:
**	Modify		: 2020/2/27		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include "defs.h"
#include "eXosip2/eXosip.h"
#include "event_handler/handler_manager.h"
#include "utils/safe_queue.h"
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

#include "utils/Singleton.h"

namespace GB28181 {

class SipServer {
public:
    SipServer();

    ~SipServer();

    static SipServer *instance();

    int Init();

    /**
     * @brief 设置本地配置
     *
     * @param sip_id sip id
     * @param host sip host
     * @param port sip port
     */
    int SetLocalConfig(const std::string &sip_id, const std::string &host, uint16_t port);

    /**
     * @brief 启动sip服务
     *
     * @param user_agent
     * @return int
     */
    int Start(const std::string &user_agent);

    int Quit();

    // 获取exoosip上下文
    eXosip_t *GetExosipContext() {
        return m_excontext;
    }

public:
    // 事件接收
    void DoReceiveEvents();


private:
    // 根据事件类型，获取事件处理器，封装成sip_event_sptr
    sip_event_sptr new_event(eXosip_t *exosip_context, eXosip_event_t *exosip_event);

private:
    bool                    m_isrun = false;

    uint16_t                         m_sipPort;      // sip port
    uint64_t                         m_eventId;      // 事件id 自增
    std::string                      m_sipId;        // sip id
    std::string                      m_sipHost;      // sip host
    eXosip_t                        *m_excontext;    // exosip上下文
    EventHandlerManager             m_eventHandle;  // 事件处理器
    std::thread                      recvTask;       // 接收事件线程

};

typedef Tools::Singleton<SipServer> g_SipServer;


}  // namespace GB28181
