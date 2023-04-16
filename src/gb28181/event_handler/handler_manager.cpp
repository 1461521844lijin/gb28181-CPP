/*
**	********************************************************************************
**
**	File		: handler_manager.cpp
**	Description	: 
**	Modify		: 2020/2/27		zhangqiang		Create the file
**	********************************************************************************
*/

#include "handler_manager.h"
#include "Util/logger.h"

#include "gb28181/device/deviceManager.h"


namespace GB28181 {

#define CALLBACK_TEMPLATE(F) (std::bind(&EventHandlerManager::F, this, std::placeholders::_1))

EventHandlerManager::EventHandlerManager()
{

    EventNameProcPair eventProcTable[EXOSIP_EVENT_COUNT] = {
            {"EXOSIP_REGISTRATION_SUCCESS",        CALLBACK_TEMPLATE(on_exosip_registration_success)},
            {"EXOSIP_REGISTRATION_FAILURE",        CALLBACK_TEMPLATE(on_exosip_registration_failure)},
            {"EXOSIP_CALL_INVITE",                 CALLBACK_TEMPLATE(on_exosip_call_invite)},
            {"EXOSIP_CALL_REINVITE",               CALLBACK_TEMPLATE(on_exosip_call_reinvite)},
            {"EXOSIP_CALL_NOANSWER",               CALLBACK_TEMPLATE(on_exosip_call_noanswer)},
            {"EXOSIP_CALL_PROCEEDING",             CALLBACK_TEMPLATE(on_exosip_call_proceeding)},
            {"EXOSIP_CALL_RINGING",                CALLBACK_TEMPLATE(on_exosip_call_ringing)},
            {"EXOSIP_CALL_ANSWERED",               CALLBACK_TEMPLATE(on_exosip_call_answered)},
            {"EXOSIP_CALL_REDIRECTED",             CALLBACK_TEMPLATE(on_exosip_call_redirected)},
            {"EXOSIP_CALL_REQUESTFAILURE",         CALLBACK_TEMPLATE(on_exosip_call_requestfailure)},
            {"EXOSIP_CALL_SERVERFAILURE",          CALLBACK_TEMPLATE(on_exosip_call_serverfailure)},
            {"EXOSIP_CALL_GLOBALFAILURE",          CALLBACK_TEMPLATE(on_exosip_call_globalfailure)},
            {"EXOSIP_CALL_ACK",                    CALLBACK_TEMPLATE(on_exosip_call_ack)},
            {"EXOSIP_CALL_CANCELLED",              CALLBACK_TEMPLATE(on_exosip_call_cancelled)},
            {"EXOSIP_CALL_MESSAGE_NEW",            CALLBACK_TEMPLATE(on_exosip_call_message_new)},
            {"EXOSIP_CALL_MESSAGE_PROCEEDING",     CALLBACK_TEMPLATE(on_exosip_call_message_proceeding)},
            {"EXOSIP_CALL_MESSAGE_ANSWERED",       CALLBACK_TEMPLATE(on_exosip_call_message_answered)},
            {"EXOSIP_CALL_MESSAGE_REDIRECTED",     CALLBACK_TEMPLATE(on_exosip_call_message_redirected)},
            {"EXOSIP_CALL_MESSAGE_REQUESTFAILURE", CALLBACK_TEMPLATE(on_exosip_call_message_requestfailure)},
            {"EXOSIP_CALL_MESSAGE_SERVERFAILURE",  CALLBACK_TEMPLATE(on_exosip_call_message_serverfailure)},
            {"EXOSIP_CALL_MESSAGE_GLOBALFAILURE",  CALLBACK_TEMPLATE(on_exosip_call_message_globalfailure)},
            {"EXOSIP_CALL_CLOSED",                 CALLBACK_TEMPLATE(on_exosip_call_closed)},
            {"EXOSIP_CALL_RELEASED",               CALLBACK_TEMPLATE(on_exosip_call_released)},
            {"EXOSIP_MESSAGE_NEW",                 CALLBACK_TEMPLATE(on_exosip_message_new)},
            {"EXOSIP_MESSAGE_PROCEEDING",          CALLBACK_TEMPLATE(on_exosip_message_proceeding)},
            {"EXOSIP_MESSAGE_ANSWERED",            CALLBACK_TEMPLATE(on_exosip_message_answered)},
            {"EXOSIP_MESSAGE_REDIRECTED",          CALLBACK_TEMPLATE(on_exosip_message_redirected)},
            {"EXOSIP_MESSAGE_REQUESTFAILURE",      CALLBACK_TEMPLATE(on_exosip_message_requestfailure)},
            {"EXOSIP_MESSAGE_SERVERFAILURE",       CALLBACK_TEMPLATE(on_exosip_message_serverfailure)},
            {"EXOSIP_MESSAGE_GLOBALFAILURE",       CALLBACK_TEMPLATE(on_exosip_message_globalfailure)},
            {"EXOSIP_SUBSCRIPTION_NOANSWER",       CALLBACK_TEMPLATE(on_exosip_subscription_noanswer)},
            {"EXOSIP_SUBSCRIPTION_PROCEEDING",     CALLBACK_TEMPLATE(on_exosip_subscription_proceeding)},
            {"EXOSIP_SUBSCRIPTION_ANSWERED",       CALLBACK_TEMPLATE(on_exosip_subscription_answered)},
            {"EXOSIP_SUBSCRIPTION_REDIRECTED",     CALLBACK_TEMPLATE(on_exosip_subscription_redirected)},
            {"EXOSIP_SUBSCRIPTION_REQUESTFAILURE", CALLBACK_TEMPLATE(on_exosip_subscription_requestfailure)},
            {"EXOSIP_SUBSCRIPTION_SERVERFAILURE",  CALLBACK_TEMPLATE(on_exosip_subscription_serverfailure)},
            {"EXOSIP_SUBSCRIPTION_GLOBALFAILURE",  CALLBACK_TEMPLATE(on_exosip_subscription_globalfailure)},
            {"EXOSIP_SUBSCRIPTION_NOTIFY",         CALLBACK_TEMPLATE(on_exosip_subscription_notify)},
            {"EXOSIP_IN_SUBSCRIPTION_NEW",         CALLBACK_TEMPLATE(on_exosip_in_subscription_new)},
            {"EXOSIP_NOTIFICATION_NOANSWER",       CALLBACK_TEMPLATE(on_exosip_notification_noanswer)},
            {"EXOSIP_NOTIFICATION_PROCEEDING",     CALLBACK_TEMPLATE(on_exosip_notification_proceeding)},
            {"EXOSIP_NOTIFICATION_ANSWERED",       CALLBACK_TEMPLATE(on_exosip_notification_answered)},
            {"EXOSIP_NOTIFICATION_REDIRECTED",     CALLBACK_TEMPLATE(on_exosip_notification_redirected)},
            {"EXOSIP_NOTIFICATION_REQUESTFAILURE", CALLBACK_TEMPLATE(on_exosip_notification_requestfailure)},
            {"EXOSIP_NOTIFICATION_SERVERFAILURE",  CALLBACK_TEMPLATE(on_exosip_notification_serverfailure)},
            {"EXOSIP_NOTIFICATION_GLOBALFAILURE",  CALLBACK_TEMPLATE(on_exosip_notification_globalfailure)}
    };
    for (uint32_t i = 0; i < EXOSIP_EVENT_COUNT; ++i)
    {
        m_eventProcMap.insert(std::make_pair(i, eventProcTable[i]));
    }
}

EventHandlerManager::~EventHandlerManager()
{
}

EventHandlerManager::EventNameProcPair EventHandlerManager::GetEventProc(eXosip_event_type_t type)
{
    if (type > EXOSIP_EVENT_COUNT)
    {
        EventNameProcPair pair = {"", nullptr};
        InfoL << "Event Type: " << type << " don't exist!";
        return pair;
    }

    auto value = m_eventProcMap.find(type);
    return value->second;
}

/* REGISTER related events */
int EventHandlerManager::on_exosip_registration_success(const SipEvent::ptr &event)
{
    // //TODO ???????1?7
    // GB28181SvrManager::instance()->OnRegisterSuccess(event->exevent->rid);
    return 0;
}

int EventHandlerManager::on_exosip_registration_failure(const SipEvent::ptr &event)
{
    ///TODO REGISTER send twice, this is question!
    WarnL << "register id: " << event->exevent->rid << " need authentication!";
    eXosip_lock(event->excontext);
    eXosip_automatic_action(event->excontext);
    eXosip_unlock(event->excontext);
    return 0;
}

/* INVITE related events within calls */
int EventHandlerManager::on_exosip_call_invite(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleInviteRequest(event);
    return 0;
}

int EventHandlerManager::on_exosip_call_reinvite(const SipEvent::ptr &event)
{
    return 0;
}


int EventHandlerManager::on_exosip_call_noanswer(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_proceeding(const SipEvent::ptr &event)
{

    m_callhandler.on_proceeding(event);
    return 0;
}


int EventHandlerManager::on_exosip_call_ringing(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleResponseProcessing(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_answered(const SipEvent::ptr &event)
{
    m_callhandler.handleResponseSuccess(event);
    
    return 0;
}

int EventHandlerManager::on_exosip_call_redirected(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_requestfailure(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_serverfailure(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_globalfailure(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_ack(const SipEvent::ptr &event)
{
    return 0;
}


int EventHandlerManager::on_exosip_call_cancelled(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleClose(event);

    return 0;
}

/* request related events within calls (except INVITE) */
int EventHandlerManager::on_exosip_call_message_new(const SipEvent::ptr &event)
{

    // 打印message
    string reqid;
    osip_generic_param_t* tag = nullptr;
    osip_to_get_tag(event->exevent->request->from, &tag);
    if (nullptr == tag || nullptr == tag->gvalue) {
        reqid = "";
    }
    reqid = (const char*)tag->gvalue;

    InfoL << "on_exosip_call_message_new response reqid = " << reqid;



    eXosip_event_t *exosip_event = event->exevent;

    if (!strncmp(exosip_event->request->sip_method, "MESSAGE", strlen("MESSAGE")))
    {
        m_msghandler.HandleIncomingReq(event);
    }
    return 0;
}

int EventHandlerManager::on_exosip_call_message_proceeding(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_call_message_answered(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleInfoResponseSuccess(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_message_redirected(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleInfoResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_message_requestfailure(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleInfoResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_message_serverfailure(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleInfoResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_call_message_globalfailure(const SipEvent::ptr &event)
{
//    m_CallHandler->HandleInfoResponseFailure(event);

    return 0;
}


// 收到下级或者上级的bye消息
int EventHandlerManager::on_exosip_call_closed(const SipEvent::ptr &event)
{
    m_callhandler.handleClose(event);
    return 0;
}

/* for both UAS & UAC events  会话释放 */ 
int EventHandlerManager::on_exosip_call_released(const SipEvent::ptr &event)
{
    // m_callhandler.handleClose(event);
    return 0;
}


/* events received for request outside calls */
int EventHandlerManager::on_exosip_message_new(const SipEvent::ptr &event)
{
    eXosip_event_t *exosip_event = event->exevent;

    if(MSG_IS_REGISTER(exosip_event->request)){
        m_registerhandler.HandleIncomingReq(event);
    }
    else if(MSG_IS_MESSAGE(exosip_event->request)){
        m_msghandler.HandleIncomingReq(event);
    }
    else if(MSG_IS_BYE(exosip_event->request)){
        WarnL << " UNKNOW METHON   MSG_IS_BYE";
    }else{
        WarnL << " UNKNOW METHON";
    }


    return 0;
}

int EventHandlerManager::on_exosip_message_proceeding(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_message_answered(const SipEvent::ptr &event)
{
    m_msghandler.HandleResponseSuccess(event);

    return 0;
}

int EventHandlerManager::on_exosip_message_redirected(const SipEvent::ptr &event)
{
//    m_msghandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_message_requestfailure(const SipEvent::ptr &event)
{
   m_msghandler.HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_message_serverfailure(const SipEvent::ptr &event)
{
//    m_msghandler->HandleResponseFailure(event);

    return 0;
}

int EventHandlerManager::on_exosip_message_globalfailure(const SipEvent::ptr &event)
{
//    m_msghandler->HandleResponseFailure(event);

    return 0;
}

/* Presence and Instant Messaging */
int EventHandlerManager::on_exosip_subscription_noanswer(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_subscription_proceeding(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_subscription_answered(const SipEvent::ptr &event)
{
//    m_pSubscribeHandler->HandleResponseSuccess(event);
    return 0;
}

int EventHandlerManager::on_exosip_subscription_redirected(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_subscription_requestfailure(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_subscription_serverfailure(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_subscription_globalfailure(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_subscription_notify(const SipEvent::ptr &event)
{
    m_msghandler.HandleIncomingReq(event);
    return 0;
}

int EventHandlerManager::on_exosip_in_subscription_new(const SipEvent::ptr &event)
{
    return 0;
}


int EventHandlerManager::on_exosip_notification_noanswer(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_notification_proceeding(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_notification_answered(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_notification_redirected(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_notification_requestfailure(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_notification_serverfailure(const SipEvent::ptr &event)
{
    return 0;
}

int EventHandlerManager::on_exosip_notification_globalfailure(const SipEvent::ptr &event)
{
    return 0;
}

}

