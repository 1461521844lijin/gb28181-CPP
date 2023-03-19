#pragma once

#include "gb28181/defs.h"
#include "base_handler.h"


namespace GB28181{


class Registerhandler : public BaseHandler
{
public:
    
public:


    //接受注册事件信息
    int HandleIncomingReq(const sip_event_sptr& e);


    /// @brief 发送未授权信息
    /// @param 
    void response_register_401unauthorized(const sip_event_sptr& e);
    
};





}
