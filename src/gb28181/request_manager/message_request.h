/*
**	********************************************************************************
**
**	File		: message_request.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include "base_request.h"


namespace GB28181 {

class MessageRequest : public BaseRequest
{
public:
    typedef std::shared_ptr<MessageRequest> ptr;
    MessageRequest(outcoming_req_type_e reqtype, const string& reqsn) : BaseRequest(reqtype), m_reqsn(reqsn) {}
    virtual ~MessageRequest() {}

    /// @brief 获取请求序列号
    const string& GetReqSn() {
        return m_reqsn;
    }

private:
    string m_reqsn;
};
typedef shared_ptr<MessageRequest> MessageRequestSptr;

///< 保活请求
class KeepaliveRequest : public MessageRequest
{
public:
    KeepaliveRequest(const string& reqsn) : MessageRequest(OUTCOMING_REQU_TYPE_KEEPALIVE, reqsn) {}
    virtual ~KeepaliveRequest() {}

    virtual int HandleResponse(int statcode);

    /// -1: keepalive failed; 200: OK
    int GetStatCode();

private:
    int m_statcode;
};

}
