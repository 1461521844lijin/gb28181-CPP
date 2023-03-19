/*
**	********************************************************************************
**
**	File		: defs.h
**	Description	: 
**	Modify		: 2020/2/27		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <memory>
#include "eXosip2/eXosip.h"
#include <functional>
using namespace std;


// namespace GB28181 {

struct sip_event_t;
typedef shared_ptr<sip_event_t> sip_event_sptr;  // sip事件信息智能指针
typedef std::function<int(const sip_event_sptr &)> event_proc;  // 事件处理函数


/**
 * @brief SIP事件封装结构体
 * 
 */
struct sip_event_t
{
    int                 value;      ///< 事件值
    const char*         name;       // 事件名称
    event_proc          proc;       // 事件处理函数
    struct eXosip_t*    excontext;  // eXosip上下文
    eXosip_event_t*     exevent;    // eXosip事件
    uint64_t            id;         // 事件id

    sip_event_t() = default;
    // ~sip_event_t(){
    //     eXosip_event_free(exevent);
    // }
};



// }

