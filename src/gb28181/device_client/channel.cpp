#include "channel.h"
#include <strstream>

namespace GB28181 {

void Channel::setParental(const std::string &parental) {
    m_parental = parental;
}
std::string Channel::getParental() const {
    return m_parental;
}
void Channel::setChannelId(const std::string &channelId) {
    m_channelId = channelId;
}
std::string Channel::getChannelId() const {
    return m_channelId;
}
void Channel::setName(const std::string &name) {
    m_name = name;
}
std::string Channel::getName() const {
    return m_name;
}
void Channel::setManufacturer(const std::string &manufacturer) {
    m_manufacturer = manufacturer;
}
std::string Channel::getManufacturer() const {
    return m_manufacturer;
}
void Channel::setModel(const std::string &model) {
    m_model = model;
}
std::string Channel::getModel() const {
    return m_model;
}
void Channel::setOwner(const std::string &owner) {
    m_owner = owner;
}
std::string Channel::getOwner() const {
    return m_owner;
}
void Channel::setCivilCode(const std::string &civilCode) {
    m_civilCode = civilCode;
}
std::string Channel::getCivilCode() const {
    return m_civilCode;
}
void Channel::setAddress(const std::string &address) {
    m_address = address;
}
std::string Channel::getAddress() const {
    return m_address;
}
void Channel::setParentId(const std::string &parentId) {
    m_parentId = parentId;
}
std::string Channel::getParentId() const {
    return m_parentId;
}
void Channel::setRegisterWay(const std::string &registerWay) {
    m_registerWay = registerWay;
}
std::string Channel::getRegisterWay() const {
    return m_registerWay;
}
void Channel::setSecrety(const std::string &secrety) {
    m_secrety = secrety;
}
std::string Channel::getSecrety() const {
    return m_secrety;
}
void Channel::setStreamNum(const std::string &sreamNum) {
    m_streamNum = sreamNum;
}
std::string Channel::getStreamNum() const {
    return m_streamNum;
}
void Channel::setIpAddress(const std::string &ipAddress) {
    m_ipAddress = ipAddress;
}
std::string Channel::getIpAddress() const {
    return m_ipAddress;
}
void Channel::setStatus(const std::string &status) {
    m_status = status;
}
std::string Channel::getStatus() const {
    return m_status;
}
void Channel::setPtztype(const std::string &ptztype) {
    m_ptztype = ptztype;
}
std::string Channel::getPtztype() const {
    return m_ptztype;
}
void Channel::setDownSpeed(const std::string &downSpeed) {
    m_downSpeed = downSpeed;
}
std::string Channel::getDownSpeed() const {
    return m_downSpeed;
}

bool Channel::insertSubChannel(const std::string parentId, const std::string &channelId, Channel::ptr channel) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (parentId == m_channelId) {
        m_subChannels[channelId] = channel;
        m_channelCount++;
        return true;
    }
    for (auto it = m_subChannels.begin(); it != m_subChannels.end(); it++) {
        if (it->second->insertSubChannel(parentId, channelId, channel)) {
            return true;
        }
    }
    return false;
}

Channel::ptr Channel::getSubChannel(const std::string &channelId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto                        it = m_subChannels.find(channelId);
    if (it != m_subChannels.end()) {
        return it->second;
    }
    return nullptr;
}

bool Channel::deleteSubChannel(const std::string &channelId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_subChannels.find(channelId) != m_subChannels.end()) {
        m_subChannels.erase(channelId);
        m_channelCount--;
        return true;
    }
    for (auto it = m_subChannels.begin(); it != m_subChannels.end(); it++) {
        if (it->second->deleteSubChannel(channelId)) {
            return true;
        }
    }
    return false;
}

std::vector<Channel::ptr> Channel::getAllSubChannels() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<Channel::ptr>   channels;
    for (auto it = m_subChannels.begin(); it != m_subChannels.end(); it++) {
        channels.push_back(it->second);
    }
    return channels;
}

int Channel::getChannelCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_channelCount;
}
void Channel::addChannelCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_channelCount++;
}
void Channel::subChannelCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_channelCount--;
    if (m_channelCount < 0) {
        m_channelCount = 0;
    }
}


std::string Channel::toString(){
    std::strstream ss;
    ss << "ChannelId:" << m_channelId << " Name:" << m_name << " Parental:" << m_parental << " Manufacturer:" << m_manufacturer << " Model:" << m_model << " Owner:" << m_owner << " CivilCode:" << m_civilCode << " Address:" << m_address << " ParentId:" << m_parentId << " RegisterWay:" << m_registerWay << " Secrety:" << m_secrety << " StreamNum:" << m_streamNum << " IpAddress:" << m_ipAddress << " Status:" << m_status << " Ptztype:" << m_ptztype << " DownSpeed:" << m_downSpeed;
    return ss.str();
}


}  // namespace GB28181
