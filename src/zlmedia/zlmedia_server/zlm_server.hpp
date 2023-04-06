#pragma once

#include <memory>
#include <mutex>

namespace ZLM {

// 流媒体服务对象类
class ZlmServer {
public:
    typedef std::shared_ptr<ZlmServer> ptr;
    ZlmServer(const std::string &zlm_addr,
              int                zlm_port,
              const std::string &zlm_secret,
              const std::string &zlm_server_id)
        : m_zlm_addr(zlm_addr),
          m_zlm_port(zlm_port),
          m_zlm_secret(zlm_secret),
          m_zlm_server_id(zlm_server_id),
          m_last_heartbeat_time(time(0)) {}

private:
    std::string m_zlm_addr;                    // 流媒体服务器地址
    int         m_zlm_port;                    // 流媒体服务器端口
    std::string m_zlm_secret;                  // 流媒体服务器密钥
    std::string m_zlm_server_id;               // 流媒体服务器ID
    bool        m_is_connected        = true;  // 流媒体服务器是否连接,默认为true
    time_t      m_last_heartbeat_time = 0;     // 最后一次心跳时间
    int         m_load                = 0;     // 负载度

    std::mutex m_mutex;

public:
    std::string &getZlmAddr();
    void         setZlmAddr(std::string &value);
    int          getZlmPort();
    void         setZlmPort(int value);
    std::string &getZlmSecret();
    void         setZlmSecret(std::string &value);
    std::string &getZlmServerId();
    void         setZlmServerId(std::string &value);
    bool         getIsConnected();
    void         setIsConnected(bool value);

    int  getLoad();
    void setLoad(int value);

    time_t getLastHeartbeatTime();
    void   setLastHeartbeatTime(time_t value);
};

}  // namespace ZLM
