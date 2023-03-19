/*
**	********************************************************************************
**
**	File		: config_manager.cpp
**	Description	: 
**	Modify		: 2020/2/28		zhangqiang		Create the file
**	********************************************************************************
*/
#include "config_manager.h"


namespace Config
{
    

ConfigManager *ConfigManager::instance()
{
    static ConfigManager _ins;
    return &_ins;
}

bool ConfigManager::Load(const std::string &path)
{
    m_node = YAML::LoadFile(path);
    return true;
}

bool ConfigManager::GetLocalSip(local_sip_t &localcfg)
{
    localcfg.svr_ip         = m_node["local_sip"]["svr_ip"].as<std::string>();
    localcfg.svr_port       = m_node["local_sip"]["svr_port"].as<uint16_t >();
    localcfg.svr_id         = m_node["local_sip"]["svr_id"].as<std::string>();
    localcfg.svr_domain     = m_node["local_sip"]["svr_domain"].as<std::string>();
    localcfg.svr_pwd        = m_node["local_sip"]["svr_pwd"].as<std::string>();
    localcfg.svr_pa         = m_node["local_sip"]["svr_pa"].as<std::string>();
    localcfg.svr_nonce      = m_node["local_sip"]["svr_nonce"].as<std::string>();
    localcfg.svr_rtpport    = m_node["local_sip"]["svr_rtpport"].as<std::string>();
    
    return true;
}

bool ConfigManager::GetRemoteSip(remote_sip_t &remotecfg)
{
    remotecfg.svr_ip = m_node["remote_sip"]["svr_ip"].as<std::string>();
    remotecfg.svr_port = m_node["remote_sip"]["svr_port"].as<uint16_t >();
    remotecfg.svr_id = m_node["remote_sip"]["svr_id"].as<std::string>();
    remotecfg.svr_domain = m_node["remote_sip"]["svr_domain"].as<std::string>();
    remotecfg.passwd = m_node["remote_sip"]["passwd"].as<std::string>();
    return true;
}

bool ConfigManager::GetLogConfig(log_config_t &logcfg)
{
    logcfg.level = m_node["log"]["level"].as<uint32_t>();
    logcfg.path = m_node["log"]["path"].as<std::string>();
    logcfg.logName = m_node["log"]["logName"].as<std::string>();
    std::string onOff = m_node["log"]["enable"].as<std::string>();
    logcfg.enable = (onOff == "on");
    return true;
}

bool ConfigManager::GetMediaPortPool(media_port_pool_t &portpool)
{
    portpool.start = m_node["media_port_pool"]["start"].as<uint32_t >();
    portpool.end = m_node["media_port_pool"]["end"].as<uint32_t >();
    return true;
}


}