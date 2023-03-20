#include "ptz_cmd.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace GB28181 {

/**
 * 云台指令码计算
 *
 * @param leftRight  镜头左移右移 0:停止 1:左移 2:右移
 * @param upDown     镜头上移下移 0:停止 1:上移 2:下移
 * @param inOut      镜头放大缩小 0:停止 1:缩小 2:放大
 * @param moveSpeed  镜头移动速度 默认 0XFF (0-255)
 * @param zoomSpeed  镜头缩放速度 默认 0X1 (0-255)
 */
std::string PtzCmd::cmdString(int leftRight, int upDown, int inOut, int moveSpeed, int zoomSpeed) {
    int cmdCode = 0;
    if (leftRight == 2) {
        cmdCode = 0x01;  // 右移
    } else if (leftRight == 1) {
        cmdCode = 0x02;  // 左移
    }
    if (upDown == 2) {
        cmdCode |= 0x04;  // 下移
    } else if (upDown == 1) {
        cmdCode |= 0x08;  // 上移
    }
    if (inOut == 2) {
        cmdCode |= 0x10;  // 放大
    } else if (inOut == 1) {
        cmdCode |= 0x20;  // 缩小
    }

    std::stringstream ss;
    // 前三字节
    ss << "A50F01";
    // 字节4 指令码
    ss << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << cmdCode;
    // 字节5 水平控制速度
    ss << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << moveSpeed;
    // 字节6 垂直控制速度
    ss << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << moveSpeed;
    // 字节7 高四位 焦距控制速度
    ss << std::setfill('0') << std::setw(1) << std::hex << std::uppercase << zoomSpeed;
    // 字节7 低四位
    ss << "0";
    // 字节8 校验码  字节8=(字节1+字节2+字节3+字节4+字节5+字节6+字节7)%256
    int checkCode =
        (0xA5 + 0x0F + 0x01 + cmdCode + moveSpeed + moveSpeed + (zoomSpeed & 0xF0)) % 0x100;
    ss << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << checkCode;

    return ss.str();
}


}  // namespace GB28181
