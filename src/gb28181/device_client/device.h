#pragma once
#include "channel.h"
#include <memory>
#include <vector>
#include <map>
#include <mutex>
namespace GB28181 {

class Device {
public:
    typedef std::shared_ptr<Device> ptr;

private:
    std::mutex m_mutex;
private:
    std::string m_deviceId;      // 设备国标编号
    std::string m_name;          // 设备名称
    std::string m_ip;            // 设备ip
    std::string m_port;          // 设备端口
    std::string m_transport;     // 设备传输协议
    int         m_status;        // 设备状态 0:离线 1:在线
    std::string m_regiestTime;   // 设备注册时间
    std::string m_lastTime;      // 设备最后一次心跳时间
    int         m_channelCount;  // 设备通道数
    std::string m_parentId;      // 设备父节点id
    int         m_callId;        // 设备呼叫id
    int         m_dialogId;      // 设备对话id

    std::map<std::string, Channel::ptr> m_subChannels;  // 子节点

public:
    Device() = default;
    Device(std::string &deviceId, std::string &ip, std::string &port);

    /**
     * @brief 添加子节点
     * 
     * @param parentId      父节点id
     * @param channelId     子节点id
     * @param channel       子节点
     */
    bool         insertSubChannel(const std::string parentId, const std::string &channelId, Channel::ptr channel);
    bool         deleteSubChannel(const std::string &channelId);
    Channel::ptr getSubChannel(const std::string &channelId);
    std::vector<Channel::ptr> getAllSubChannels();

    std::string getDeviceId() const;
    void        setDeviceId(std::string &deviceId);

    std::string getName() const;
    void        setName(std::string &name);

    std::string getIp() const;
    void        setIp(std::string &ip);

    std::string getPort() const;
    void        setPort(std::string &port);

    std::string getTransport() const;
    void        setTransport(std::string &transport);


    int  getStatus() const;
    void setStatus(int status);

    std::string getRegiestTime() const;
    void        setRegiestTime(std::string regiestTime);

    std::string getLastTime() const;
    void        setLastTime(std::string &lastTime);

    int  getChannelCount() const;
    void setChannelCount(int channelCount);

    std::string getParentId() const;
    void        setParentId(std::string &parentId);

    int  getCallId() const;
    void setCallId(int callId);

    int  getDialogId() const;
    void setDialogId(int dialogId);

    std::string toString() const;
};

}  // namespace GB28181
