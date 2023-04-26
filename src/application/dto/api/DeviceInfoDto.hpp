#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)


namespace DTO::GETWAY 
{

    // std::string m_deviceId;      // 设备国标编号
    // std::string m_name;          // 设备名称
    // std::string m_ip;            // 设备ip
    // std::string m_port;          // 设备端口
    // std::string m_transport;     // 设备传输协议
    // int         m_status;        // 设备状态 0:离线 1:在线
    // std::string m_regiestTime;   // 设备注册时间
    // std::string m_lastTime;      // 设备最后一次心跳时间
    // int         m_channelCount;  // 设备通道数
    class  DeviceInfoDto : public oatpp::DTO 
    {
        DTO_INIT(DeviceInfoDto, DTO)
        DTO_FIELD(String, device_id);
        DTO_FIELD(String, device_name);
        DTO_FIELD(String, device_ip);
        DTO_FIELD(String, device_port);
        DTO_FIELD(String, device_transport);
        DTO_FIELD(Int32, device_status);
        DTO_FIELD(String, device_regiest_time);
        DTO_FIELD(String, device_last_time);
        DTO_FIELD(Int32, device_channel_count);
    };




    
} // namespace DTO:

#include OATPP_CODEGEN_END(DTO)


