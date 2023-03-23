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

    REQ_TYPE_MAX
};



}

