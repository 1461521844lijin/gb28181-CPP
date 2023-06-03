#include "call_handler.h"

#include "Util/logger.h"
#include "gb28181/device/call_session.h"
#include "gb28181/device/deviceManager.h"

namespace GB28181 {

int CallHandler::handleResponseSuccess(const SipEvent::ptr event) {
    std::string deviceid = event->exevent->request->to->url->username;
    int         callid   = event->exevent->cid;
    int         dialog   = event->exevent->did;

    InfoL << "on_exosip_call_answered deviceid=" << deviceid << " callid=" << callid
          << " dialog=" << dialog;

    auto device = g_deviceMgr::GetInstance()->getDevice(deviceid);
    if (!device) {
        InfoL << "deviceid=" << deviceid << " not exist";
        return -1;
    }
    auto sessions = GB28181::g_StreamMgr::GetInstance()->getStreamByType(STREAM_TYPE_GB);
    for (auto session : sessions) {
        auto call_sessioned = std::dynamic_pointer_cast<GB28181::CallSession>(session);
        if (call_sessioned->getCallId() == callid) {
            call_sessioned->setDialogId(dialog);
            call_sessioned->setConnected(true);
            sendCallAck(event->excontext, dialog);
            return 0;
        }
    }
    WarnL << "没有找到对应的call session";
    return -1;
}

int CallHandler::on_proceeding(const SipEvent::ptr event) {
    std::string           reqid;
    osip_generic_param_t *tag = nullptr;
    osip_to_get_tag(event->exevent->request->from, &tag);
    if (nullptr == tag || nullptr == tag->gvalue) {
        reqid = "";
    }
    reqid = (const char *)tag->gvalue;

    InfoL << "on_exosip_call_proceeding response reqid = " << reqid;
    return 0;
}

int CallHandler::handleClose(const SipEvent::ptr event) {
    int         callid   = event->exevent->cid;
    int         dialog   = event->exevent->did;
    std::string deviceid = event->exevent->request->from->url->username;
    InfoL << "on_exosip_call_closed deviceid=" << deviceid;
    auto sessions = GB28181::g_StreamMgr::GetInstance()->getStreamByType(STREAM_TYPE_GB);
    for (auto session : sessions) {
        auto call_sessioned = std::dynamic_pointer_cast<GB28181::CallSession>(session);
        if (call_sessioned->getDialogId() == dialog) {
            call_sessioned->setConnected(false);
            InfoL << "收到来自 deviceid=" << deviceid << "的挂断请求"
                  << " callid=" << callid << " dialog=" << dialog;
            return 0;
        }
    }
    WarnL << "没有找到对应的call session";
    return -1;
}

}  // namespace GB28181
