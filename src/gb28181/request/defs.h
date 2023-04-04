/*
**	********************************************************************************
**
**	File		: defs.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once


namespace GB28181 {


/// @brief 请求类型枚举
enum REQ_MESSAGE_TYPE
{
    REQ_TYPE_UNKNOWN    =0,
    KEEPALIVE,              // 保活心跳
    QUIRY_CATALOG,          // 查询目录
    DEVICE_CONTROL_PTZ,     // 设备控制-云台
    DEVICE_QUIER_PRESET,    // 设备查询-预置位
    DEVICE_CONTROL_PRESET,  // 设备控制-预置位

    REQ_TYPE_MAX
};



}

