/*
**	********************************************************************************
**
**	File		: config_manager.h
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include "yaml-cpp/yaml.h"


namespace Config
{
    


struct local_sip_t {
    uint16_t        svr_port;       // sip server port
    std::string     svr_id;         // sip server id
    std::string     svr_ip;         // sip server ip
    std::string     svr_domain;     // sip server domain
    std::string     svr_pwd;        // sip server password
    std::string     svr_pa;         // sip server proxy agent
    std::string     svr_nonce;      // sip server nonce
    std::string     svr_rtpport;    // sip server rtp port
};

struct remote_sip_t : public local_sip_t {
    std::string     passwd;
};

struct media_port_pool_t {
    uint32_t start;
    uint32_t end;
};

struct log_config_t {
    bool        enable;
    int         level;
    std::string path;
    std::string logName;
};

class ConfigManager
{
public:
    ConfigManager() = default;
    ~ConfigManager() = default;

    static ConfigManager* instance();

    /// 加载配置文件
    bool Load(const std::string& path);

    bool GetLocalSip(local_sip_t& localcfg);

    bool GetRemoteSip(remote_sip_t& remotecfg);

    bool GetLogConfig(log_config_t& logcfg);

    bool GetMediaPortPool(media_port_pool_t& portpool);

private:
    YAML::Node  m_node;
};

} // namespace Config

