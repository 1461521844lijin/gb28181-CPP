/*
**	********************************************************************************
**
**	File		: base_request.h
**	Description	:
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include "defs.h"
#include "eXosip2/eXosip.h"
#include "gb28181/device_client/device.h"
#include <condition_variable>
#include <map>
#include <memory>
#include <sstream>

namespace GB28181 {
using namespace std;


struct exosip_guard {
    explicit exosip_guard(eXosip_t* e) {
        m_excontext = e;
        eXosip_lock(m_excontext);
    }
    ~exosip_guard() {
        eXosip_unlock(m_excontext);
    }
    eXosip_t* m_excontext;
};


class BaseRequest {
public:
    typedef std::shared_ptr<BaseRequest> ptr;
    explicit BaseRequest(REQ_MESSAGE_TYPE reqtype);
    virtual ~BaseRequest();

    /// @brief 请求响应接口 虚函数被子类重写
    virtual int HandleResponse(int statcode) {
        return 0;
    };

    // 设置是否等待
    void SetWait(bool bwait = true);

    /// 等待请求完成 如果设置了bwait为true则会阻塞等待请求完成，否则直接返回
    void WaitResult();

    /// 请求是否完成
    bool IsFinished();

    /// 设置请求ID
    int SetReqid(string &id);

    /// @brief 获取请求类型
    /// @return 请求类型
    REQ_MESSAGE_TYPE GetReqType();

    /// @brief 获取请求时间
    time_t GetReqtime();

    /// @brief 标志请求完成 会唤醒等待的请求
    int onRequestFinished();

public:
    /// @brief 唤醒等待的请求
    void finished();

    // 获取请求ID
    const char *get_reqid_from_request(osip_message_t *msg);

protected:
    string m_reqid;  ///< 请求ID

private:
    bool               m_bfinished;  ///< 请求是否完成
    bool               m_bwait;      ///< 是否等待请求完成
    time_t             m_reqtime;    ///< 请求时间
    REQ_MESSAGE_TYPE   m_reqtype;    ///< 请求类型
    mutex              m_mutex;
    condition_variable m_cond;
};

class MessageRequest : public BaseRequest, public std::enable_shared_from_this<BaseRequest> {
public:
    typedef std::shared_ptr<MessageRequest> ptr;
    MessageRequest(Device::ptr device, REQ_MESSAGE_TYPE reqtype)
        : BaseRequest(reqtype), m_device(device) {}
    virtual ~MessageRequest() {}

public:
    // 发送请求
    // 是否需要等待回调  true会将请求结束后加入请求池，等收到回复后调用回调函数
    virtual int send_message(bool needcb = true);

    /// @brief 获取请求序列号
    const string &GetReqSn() {
        return m_reqsn;
    }

protected:
    // 构建消息体
    virtual const std::string make_manscdp_body() = 0;

    Device::ptr get_device() {
        return m_device;
    }

    void set_reqsn(const std::string &reqsn) {
        m_reqsn = reqsn;
    }

    std::string &get_reqsn() {
        return m_reqsn;
    }

private:
    string      m_reqsn;   // 请求序列号
    Device::ptr m_device;  // 请求发往的设备
};



}  // namespace GB28181
