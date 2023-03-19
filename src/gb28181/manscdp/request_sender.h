/*
**	********************************************************************************
**
**	File		: msg_sender.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <atomic>
#include <osipparser2/osip_message.h>
#include "utils/config_manager.h"
#include "gb28181/request_manager/base_request.h"
#include "gb28181/device_client/device.h"


namespace GB28181 {

using namespace Config;
using namespace std;

class MsgSender
{
public:
    MsgSender();
    ~MsgSender();

    int RegisterOnline(remote_sip_t &remote);

    // 向上级平台发送保活请求
    int Keepalive(remote_sip_t &remote, local_sip_t &local, bool bwait, BaseRequest::ptr &request);
    
    /**
     * @brief 向下级设备发送查询请求
     * 
     * @param device 
     * @return int 
     */
    static int CatalogQuery(Device::ptr device);

private:
    string generate_sn();

    int send_message(remote_sip_t &remote, const char *body, BaseRequest::ptr &request);

    const char * get_reqid_from_request(osip_message_t* msg);

private:
    atomic<uint64_t > m_sn;
};

}
