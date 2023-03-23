#pragma once

#include <atomic>
#include <osipparser2/osip_message.h>
#include "gb28181/request/base_request.h"
#include "gb28181/device_client/device.h"
#include "gb28181/request/defs.h"

namespace GB28181 {
    
using namespace std;

class MsgSender
{
public:
    typedef std::shared_ptr<MsgSender> ptr;
    static MsgSender *instance();
public:
    MsgSender();
    ~MsgSender();
    

    /**
     * @brief 向下级设备发送控制请求
     * 
     * @param deviceid 设备id
     * @param type   请求类型
     */
    int send_message(std::string &deviceId, REQ_MESSAGE_TYPE type, bool bwait = false);


private:
    string generate_sn();

    // int send_message(remote_sip_t &remote, const char *body, BaseRequest::ptr &request);

    const char * get_reqid_from_request(osip_message_t* msg);

private:
    atomic<uint64_t > m_sn = 0;
};



}
