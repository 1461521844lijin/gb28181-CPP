#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <vector>
namespace GB28181 {

/*
 * 通道信息 设备目录信息
 */
class Channel {
public:
    typedef std::shared_ptr<Channel> ptr;

private:
    std::mutex m_mutex;

private:
    std::string m_parentId;      // 父节点id
    std::string m_channelId;     // 节点id
    std::string m_name;          // 设备/节点名称
    std::string m_manufacturer;  // 厂商名称
    std::string m_model;         // 型号
    std::string m_owner;         // 设备归属
    std::string m_civilCode;     // 行政区划代码
    std::string m_address;       // 设备地址
    std::string m_parental;      // 0设备 大于0存在子目录
    std::string m_registerWay;   // 注册方式
    std::string m_secrety;       // 保密属性
    std::string m_streamNum;      // 视频流数量
    std::string m_ipAddress;     // 设备IP地址
    std::string m_status;        // 设备状态 ON表示在线,OFF表示离线

    int m_channelCount;  // 子目录数量

    // info
    // 摄像机类型扩展,标识摄像机类型:1-球机;2-半球;3-固定枪机;4-遥控枪机。当目录项为摄像机时可选。
    std::string m_ptztype;
    // 下载倍速范围(可选),各可选参数以“/”分隔,如设备支持1,2,4倍速下载则应写为“1/2/4”
    std::string m_downSpeed;

    std::map<std::string, Channel::ptr> m_subChannels;  // 子节点

public:
    Channel(/* args */) = default;
    ~Channel()          = default;

    bool                      insertSubChannel(const std::string parentId, const std::string &channelId, Channel::ptr channel);
    Channel::ptr              getSubChannel(const std::string &channelId);
    bool                      deleteSubChannel(const std::string &channelId);
    std::vector<Channel::ptr> getAllSubChannels();

    int getChannelCount();
    void addChannelCount();
    void subChannelCount();

    std::string toString();

    void        setParentId(const std::string &parentId);
    std::string getParentId() const;

    void        setChannelId(const std::string &channelId);
    std::string getChannelId() const;

    void        setName(const std::string &name);
    std::string getName() const;

    void        setManufacturer(const std::string &manufacturer);
    std::string getManufacturer() const;

    void        setModel(const std::string &model);
    std::string getModel() const;

    void        setOwner(const std::string &owner);
    std::string getOwner() const;

    void        setCivilCode(const std::string &civilCode);
    std::string getCivilCode() const;

    void        setAddress(const std::string &address);
    std::string getAddress() const;

    void        setParental(const std::string &parental);
    std::string getParental() const;

    void        setRegisterWay(const std::string &registerWay);
    std::string getRegisterWay() const;

    void        setSecrety(const std::string &secrety);
    std::string getSecrety() const;

    void        setStreamNum(const std::string &sreamNum);
    std::string getStreamNum() const;

    void        setIpAddress(const std::string &ipAddress);
    std::string getIpAddress() const;

    void        setStatus(const std::string &status);
    std::string getStatus() const;

    void        setPtztype(const std::string &ptztype);
    std::string getPtztype() const;

    void        setDownSpeed(const std::string &downSpeed);
    std::string getDownSpeed() const;
};

}  // namespace GB28181
