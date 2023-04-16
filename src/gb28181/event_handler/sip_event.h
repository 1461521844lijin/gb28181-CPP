#pragma once

#include <eXosip2/eXosip.h>
#include <memory>
#include <functional>

namespace GB28181 {




class SipEvent : public std::enable_shared_from_this<SipEvent>
{
public:
typedef std::shared_ptr<SipEvent> ptr;
typedef std::function<int(const SipEvent::ptr &)> event_proc;  // 事件处理函数

public:
    int                 value;      ///< 事件值
    const char*         name;       // 事件名称
    event_proc          proc;       // 事件处理函数
    struct eXosip_t*    excontext;  // eXosip上下文
    eXosip_event_t*     exevent;    // eXosip事件
    uint64_t            id;         // 事件id
};

}