/*
**	********************************************************************************
**
**	File		: handler_manager.h
**	Description	:
**	Modify		: 2020/2/27		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include "call_handler.h"

#include "message_handler.h"
#include "register_handler.h"
#include <eXosip2/eXosip.h>
#include <map>
#include "gb28181/event_handler/sip_event.h"

namespace GB28181 {

class EventHandlerManager {
public:
    EventHandlerManager();

    ~EventHandlerManager();

    typedef struct {
        const char *name;
        SipEvent::event_proc  proc;
    } EventNameProcPair;

public:
    /**
     * @brief 获取事件类型的处理方法
     *
     * @param type 事件类型
     * @return EventNameProcPair
     */
    EventNameProcPair GetEventProc(eXosip_event_type_t type);

public:
    /* REGISTER related events */
    int on_exosip_registration_success(const SipEvent::ptr &event);
    int on_exosip_registration_failure(const SipEvent::ptr &event);

public:
    /* INVITE related events within calls */
    int on_exosip_call_invite(const SipEvent::ptr &event);
    int on_exosip_call_reinvite(const SipEvent::ptr &event);
    int on_exosip_call_noanswer(const SipEvent::ptr &event);
    int on_exosip_call_proceeding(const SipEvent::ptr &event);
    int on_exosip_call_ringing(const SipEvent::ptr &event);
    int on_exosip_call_answered(const SipEvent::ptr &event);
    int on_exosip_call_redirected(const SipEvent::ptr &event);
    int on_exosip_call_requestfailure(const SipEvent::ptr &event);
    int on_exosip_call_serverfailure(const SipEvent::ptr &event);
    int on_exosip_call_globalfailure(const SipEvent::ptr &event);
    int on_exosip_call_ack(const SipEvent::ptr &event);
    int on_exosip_call_cancelled(const SipEvent::ptr &event);

public:
    /* request related events within calls (except INVITE) */
    int on_exosip_call_message_new(const SipEvent::ptr &event);
    int on_exosip_call_message_proceeding(const SipEvent::ptr &event);
    int on_exosip_call_message_answered(const SipEvent::ptr &event);
    int on_exosip_call_message_redirected(const SipEvent::ptr &event);
    int on_exosip_call_message_requestfailure(const SipEvent::ptr &event);
    int on_exosip_call_message_serverfailure(const SipEvent::ptr &event);
    int on_exosip_call_message_globalfailure(const SipEvent::ptr &event);
    int on_exosip_call_closed(const SipEvent::ptr &event);

public:
    /* for both UAS & UAC events */
    int on_exosip_call_released(const SipEvent::ptr &event);

public:
    /* events received for request outside calls */
    int on_exosip_message_new(const SipEvent::ptr &event);
    int on_exosip_message_proceeding(const SipEvent::ptr &event);
    int on_exosip_message_answered(const SipEvent::ptr &event);
    int on_exosip_message_redirected(const SipEvent::ptr &event);
    int on_exosip_message_requestfailure(const SipEvent::ptr &event);
    int on_exosip_message_serverfailure(const SipEvent::ptr &event);
    int on_exosip_message_globalfailure(const SipEvent::ptr &event);

public:
    /* Presence and Instant Messaging */
    int on_exosip_subscription_noanswer(const SipEvent::ptr &event);
    int on_exosip_subscription_proceeding(const SipEvent::ptr &event);
    int on_exosip_subscription_answered(const SipEvent::ptr &event);
    int on_exosip_subscription_redirected(const SipEvent::ptr &event);
    int on_exosip_subscription_requestfailure(const SipEvent::ptr &event);
    int on_exosip_subscription_serverfailure(const SipEvent::ptr &event);
    int on_exosip_subscription_globalfailure(const SipEvent::ptr &event);
    int on_exosip_subscription_notify(const SipEvent::ptr &event);

public:
    int on_exosip_in_subscription_new(const SipEvent::ptr &event);

public:
    int on_exosip_notification_noanswer(const SipEvent::ptr &event);
    int on_exosip_notification_proceeding(const SipEvent::ptr &event);
    int on_exosip_notification_answered(const SipEvent::ptr &event);
    int on_exosip_notification_redirected(const SipEvent::ptr &event);
    int on_exosip_notification_requestfailure(const SipEvent::ptr &event);
    int on_exosip_notification_serverfailure(const SipEvent::ptr &event);
    int on_exosip_notification_globalfailure(const SipEvent::ptr &event);

private:
    std::map<uint32_t, EventNameProcPair> m_eventProcMap;
    MessageHandler                        m_msghandler;
    Registerhandler                       m_registerhandler;
};

}  // namespace GB28181
