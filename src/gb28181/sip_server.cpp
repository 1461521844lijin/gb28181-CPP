/*
**	********************************************************************************
**
**	File		: sip_server.h
**	Description	:
**	Modify		: 2020/2/27		zhangqiang		Create the file
**	********************************************************************************
*/
#include "sip_server.h"
#include "Poller/EventPoller.h"
#include "event_handler/handler_manager.h"
#include <glog/logging.h>
#include <netinet/in.h>
#include "gb28181/event_handler/sip_event.h"
#include "gb28181/request/requested_pool.h"
#include "zlmedia/zlmedia_server/zlm_manager.hpp"
namespace GB28181 {

SipServer *SipServer::instance() {
    static SipServer server;
    return &server;
}

SipServer::SipServer() : m_sipPort(5060), m_eventId(1000000000), m_excontext(nullptr) {}

SipServer::~SipServer() = default;

int SipServer::Init() {
    m_excontext = eXosip_malloc();
    int ret = eXosip_init(m_excontext);
    if (ret != 0) {
        LOG(INFO) << "eXosip_init failed, ret=" << ret;
        return -1;
    }
    LOG(INFO) << "eXosip_init successfully!";
    return 0;
}

int SipServer::SetLocalConfig(const std::string &sip_id, const std::string &host, uint16_t port) {
    m_sipId   = sip_id;
    m_sipHost = host;
    m_sipPort = port;

    return 0;
}

int SipServer::Start(const std::string &user_agent) {
    int ret =
        eXosip_listen_addr(m_excontext, IPPROTO_UDP, m_sipHost.c_str(), m_sipPort, AF_INET, 0);
    if (ret != 0) {
        eXosip_quit(m_excontext);
        LOG(INFO) << "eXosip_listen_addr failed, ret: " << ret;
        return -1;
    } else {
        LOG(INFO) << "sipserver start on " << m_sipHost << ":" << m_sipPort
                  << "  sipid=" << m_sipId;
    }

    if (user_agent.length() > 0)
        eXosip_set_user_agent(m_excontext, user_agent.c_str());

    m_isrun = true;

    // 启动事件接受线程
    recvTask = std::thread(&SipServer::DoReceiveEvents, this);
    // 启动请求超时检查计时器
    g_RequestedPool::GetInstance()->Init();
    // 启动流媒体服务器负载检查和心跳检测计时器
    ZLM::g_ZlmMgr::GetInstance()->init();

    return 0;
}

int SipServer::Quit() {
    m_isrun = false;
    eXosip_quit(m_excontext);
    return 0;
}

void SipServer::DoReceiveEvents() {
    while (m_isrun) {
        eXosip_event_t *exosip_event;

        exosip_event = eXosip_event_wait(m_excontext, 0, 20);

        if (exosip_event == nullptr) {
            eXosip_automatic_action(m_excontext);
            osip_usleep(100000);
            continue;
        }

        SipEvent::ptr sip_event = new_event(m_excontext, exosip_event);
        if (nullptr == sip_event)
            continue;

        LOG(INFO) << "收到event: " << sip_event->name << ", id=" << sip_event->id;
        toolkit::EventPollerPool::Instance().getExecutor()->async([sip_event]() {
            sip_event->proc(sip_event);
            eXosip_event_free(sip_event->exevent);
        });
    }
}

SipEvent::ptr SipServer::new_event(eXosip_t *exosip_context, eXosip_event_t *exosip_event) {
    if (exosip_event == nullptr)
        return nullptr;

    if (exosip_event->type < EXOSIP_REGISTRATION_SUCCESS ||
        exosip_event->type > EXOSIP_NOTIFICATION_GLOBALFAILURE)
        return nullptr;

    SipEvent::ptr event = std::make_shared<SipEvent>();
    EventHandlerManager::EventNameProcPair pair = m_eventHandle.GetEventProc(exosip_event->type);
    if (pair.name == nullptr)
        return nullptr;

    event->name      = pair.name;
    event->proc      = pair.proc;
    event->excontext = exosip_context;
    event->exevent   = exosip_event;
    event->id        = m_eventId++;

    return event;
}


string SipServer::generate_sn()
{
    stringstream sn;
    sn << m_sn.fetch_add(1);
    return sn.str();
}





}  // namespace GB28181
