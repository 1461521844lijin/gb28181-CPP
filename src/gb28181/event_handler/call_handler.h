/*
**	********************************************************************************
**
**	File		: call_handler.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include "base_handler.h"
#include "./sdp/call_defs.h"


namespace GB28181 {

class CallHandler : public BaseHandler
{
public:
    CallHandler();
    virtual ~CallHandler();

    int HandleIncomingCall(const SipEvent::ptr &e);

private:
    int on_call_play_req(const SipEvent::ptr &e, const sdp_description_t &req_sdp);
    int on_call_playback_req(const SipEvent::ptr &e, const sdp_description_t &req_sdp);
    int on_call_download_req(const SipEvent::ptr &e, const sdp_description_t &req_sdp);
    int on_call_talk_req(const SipEvent::ptr &e, const sdp_description_t &req_sdp);
};

}
