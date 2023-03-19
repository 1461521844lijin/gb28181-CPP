#include "device.h"

namespace GB28181 {

Device::Device(std::string &deviceId, std::string &ip, std::string &port) {
    m_deviceId = deviceId;
    m_ip       = ip;
    m_port     = port;
}

std::string Device::getDeviceId() const {
    return m_deviceId;
}

void Device::setDeviceId(std::string &deviceId) {
    m_deviceId = deviceId;
}

std::string Device::getName() const {
    return m_name;
}

void Device::setName(std::string &name) {
    m_name = name;
}

std::string Device::getIp() const {
    return m_ip;
}

void Device::setIp(std::string &ip) {
    m_ip = ip;
}

std::string Device::getPort() const {
    return m_port;
}

void Device::setPort(std::string &port) {
    m_port = port;
}

std::string Device::getManufacturer() const {
    return m_manufacturer;
}

void Device::setManufacturer(std::string &manufacturer) {
    m_manufacturer = manufacturer;
}

std::string Device::getModel() const {
    return m_model;
}

void Device::setModel(std::string &model) {
    m_model = model;
}

std::string Device::getTransport() const {
    return m_transport;
}

void Device::setTransport(std::string &transport) {
    m_transport = transport;
}

std::string Device::getFirmware() const {
    return m_firmware;
}

void Device::setFirmware(std::string &firmware) {
    m_firmware = firmware;
}

int Device::getStatus() const {
    return m_status;
}

void Device::setStatus(int status) {
    m_status = status;
}

std::string Device::getRegiestTime() const {
    return m_regiestTime;
}

void Device::setRegiestTime(std::string &regiestTime) {
    m_regiestTime = regiestTime;
}

std::string Device::getLastTime() const {
    return m_lastTime;
}

void Device::setLastTime(std::string &lastTime) {
    m_lastTime = lastTime;
}

int Device::getChannelCount() const {
    return m_channelCount;
}

void Device::setChannelCount(int channelCount) {
    m_channelCount = channelCount;
}

std::string Device::getParentId() const {
    return m_parentId;
}

void Device::setParentId(std::string &parentId) {
    m_parentId = parentId;
}

int Device::getCallId() const {
    return m_callId;
}

void Device::setCallId(int callId) {
    m_callId = callId;
}

int Device::getDialogId() const {
    return m_dialogId;
}

void Device::setDialogId(int dialogId) {
    m_dialogId = dialogId;
}

std::string Device::toString() const {
    std::string str = "DeviceId: " + m_deviceId + "\n" + "Name: " + m_name + "\n" + "Ip: " + m_ip +
                      "\n" + "Port: " + m_port + "\n" + "Manufacturer: " + m_manufacturer + "\n" +
                      "Model: " + m_model + "\n" + "Transport: " + m_transport + "\n" +
                      "Firmware: " + m_firmware + "\n" + "Status: " + std::to_string(m_status) +
                      "\n" + "RegiestTime: " + m_regiestTime + "\n" + "LastTime: " + m_lastTime +
                      "\n" + "ChannelCount: " + std::to_string(m_channelCount) + "\n" +
                      "ParentId: " + m_parentId + "\n";
    return str;
}

}