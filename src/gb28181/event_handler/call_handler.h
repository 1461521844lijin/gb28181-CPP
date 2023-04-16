#pragma once

#include <memory>

#include "gb28181/event_handler/sip_event.h"
#include "gb28181/event_handler/base_handler.h"


namespace GB28181 
{
    
class CallHandler : public BaseHandler
{
public:
    typedef std::shared_ptr<CallHandler> ptr;
    CallHandler() = default;
    ~CallHandler() =default;
private:
    
public:


    // 呼叫成功事件响应
    int handleResponseSuccess(const SipEvent::ptr event);

    // 呼叫状态维持响应
    int on_proceeding(const SipEvent::ptr event);

    // 收到下级或者上级的bye请求
    int handleClose(const SipEvent::ptr event);

};






    
} // namespace 
