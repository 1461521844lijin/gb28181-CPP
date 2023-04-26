#pragma once 

#include "gb28181/request/base_request.h"
#include "zlmedia/zlmedia_server/zlm_server.hpp"

namespace GB28181
{
    class InviteRequest : public BaseRequest, public std::enable_shared_from_this<BaseRequest> {
public:
    typedef std::shared_ptr<InviteRequest> ptr;
    InviteRequest(Device::ptr device, const std::string &channelId, ZLM::ZlmServer::ptr zlm_server ,REQ_MESSAGE_TYPE reqtype = REQ_CALL_INVITE)
        : BaseRequest(reqtype), m_device(device), m_channel_id(channelId), m_zlm_server(zlm_server) {}
    virtual ~InviteRequest() {}

    virtual int send_call(bool needcb = true);

protected:
    // 构建消息体
    virtual const std::string make_sdp_body();

    Device::ptr get_device() {
        return m_device;
    }

private:
    Device::ptr m_device;  // 请求发往的设备
    std::string m_channel_id;  // 请求的通道id
    std::string m_rtp_port = "10000";  // 指定发送往数据的zlm的rtp端口
    ZLM::SSRCInfo::ptr m_ssrc_info;
    ZLM::ZlmServer::ptr m_zlm_server;
};



} // namespace GB28181
