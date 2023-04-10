#include "call_handler.h"

#include "glog/logging.h"
#include "gb28181/device/deviceManager.h"
#include "gb28181/device/call_session.h"

namespace GB28181
{


int CallHandler::handleResponseSuccess(const SipEvent::ptr event){

    std::string deviceid = event->exevent->request->to->url->username;
    int callid = event->exevent->cid;
    int dialog = event->exevent->did;

    LOG(INFO) << "on_exosip_call_answered deviceid=" << deviceid << " callid=" << callid << " dialog=" << dialog;

    auto device = g_deviceMgr::GetInstance()->getDevice(deviceid);
    if (!device) {
        LOG(INFO) << "deviceid=" << deviceid << " not exist";
        return -1;
    }
    // device->setCallId(callid);
    // device->setDialogId(dialog);
    auto session =  GB28181::g_CallSessionMgr::GetInstance()->getCallSession(deviceid);
    if(session){
        session->setCallId(callid);
        session->setDialogId(dialog);
        session->setConnected(true);
    }
    std::string reqid;
    osip_generic_param_t* tag = nullptr;
    osip_to_get_tag(event->exevent->request->from, &tag);
    if (nullptr == tag || nullptr == tag->gvalue) {
        reqid = "";
    }
    reqid = (const char*)tag->gvalue;

    LOG(INFO) << "on_exosip_call_answered response reqid = " << reqid;

    

    sendCallAck(event->excontext, dialog);
    return 0;
}


int CallHandler::on_proceeding(const SipEvent::ptr event){
    std::string reqid;
    osip_generic_param_t* tag = nullptr;
    osip_to_get_tag(event->exevent->request->from, &tag);
    if (nullptr == tag || nullptr == tag->gvalue) {
        reqid = "";
    }
    reqid = (const char*)tag->gvalue;

    LOG(INFO) << "on_exosip_call_proceeding response reqid = " << reqid;
    return 0;
}


int CallHandler::handleClose(const SipEvent::ptr event){

    




}



    
} // namespace GB28181
