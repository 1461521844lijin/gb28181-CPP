#pragma once

#include <memory>
#include <mutex>
#include <utility>

#include "application/dto/configs/SipConfigDto.hpp"
#include "oatpp/core/macro/component.hpp"
#include "ssrc_config.h"
namespace ZLM {

// 流媒体服务对象类
class ZlmServer {
public:
    typedef std::shared_ptr<ZlmServer> ptr;
    ZlmServer(std::string        zlm_addr,
              int                zlm_port,
              std::string        zlm_secret,
              const std::string &zlm_server_id)
        : m_zlm_addr(std::move(zlm_addr)),
          m_zlm_port(zlm_port),
          m_zlm_secret(std::move(zlm_secret)),
          m_zlm_server_id(zlm_server_id),
          m_last_heartbeat_time(time(nullptr)) {
        OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);
        m_ssrc_config = std::make_shared<SSRCConfig>(zlm_server_id, sipConfig->sipDimain);
    }

private:
    std::string m_zlm_addr;                    // 流媒体服务器地址
    int         m_zlm_port;                    // 流媒体服务器端口
    std::string m_zlm_secret;                  // 流媒体服务器密钥
    std::string m_zlm_server_id;               // 流媒体服务器ID
    bool        m_is_connected        = true;  // 流媒体服务器是否连接,默认为true
    time_t      m_last_heartbeat_time = 0;     // 最后一次心跳时间
    int         m_load                = 0;     // 负载度

    SSRCConfig::ptr m_ssrc_config;  // ssrc配置

    std::mutex m_mutex;

public:
    /**
     * @brief 向流媒体服务器发起请求，申请分配一个随机的rtp接收端口
     * @param streamid 指定流id
     * @param isPlayback 是否是回放
     */
    SSRCInfo::ptr openRTPServer(const std::string &streamid, bool isPlayback = false);

    /**
     * @brief 搜索文件系统，获取流对应的录像文件列表或日期文件夹列表
     * @param app 应用名
     * @param streamid 流id
     * @param period 录像文件的时间段，格式为：2020-01-01
     */
    std::string getMp4RecordFile(const std::string &app,
                                 const std::string &streamid,
                                 const std::string &period);

    /**
     * @brief 开始录像
     * @param app 应用名
     * @param streamid 流id
     * @param maxSecond mp4录像切片时间大小,单位秒，置0则采用配置项
     */
    std::string startRecordMp4(const std::string &app,
                               const std::string &streamid,
                               const int          maxSecond);

    /**
     * @brief 停止录像
     * @param app 应用名
     * @param streamid 流id
     */
    std::string stopRecordMp4(const std::string &app, const std::string &streamid);

    /**
     * @brief 获取录像状态
     * @param app 应用名
     * @param streamid 流id
     */
    std::string getRecordStatus(const std::string &app, const std::string &streamid);

    /**
     * @brief 获取截图或生成实时截图并返回
     */
    std::string getSnap(const std::string &url);

    // 设置录像流播放速度
    std::string setRecordSpeed(const std::string &path, const float &speed);

    bool addStreamProxy(const std::string &streamUrl,
                        const std::string &app,
                        const std::string &streamid);

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

    SSRCConfig::ptr getSsrcConfig();
    void            setSsrcConfig(SSRCConfig::ptr value);
};

}  // namespace ZLM
