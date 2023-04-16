#pragma once

#include "base_handler.h"


namespace GB28181{


class Registerhandler : public BaseHandler
{
public:
    
public:


    //接受注册事件信息
    int HandleIncomingReq(const SipEvent::ptr& e);


    /// @brief 发送未授权信息
    /// @param 
    void response_register_401unauthorized(const SipEvent::ptr& e);
    
};





}
