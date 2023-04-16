#ifndef AppComponent_hpp
#define AppComponent_hpp

#include <cstdlib>
#include <iostream>


#include "oatpp/core/base/CommandLineArguments.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "application/dto/configs/ConfigDto.hpp"
#include "application/dto/configs/WebConfigDto.hpp"
#include "application/dto/configs/LogConfigDto.hpp"
#include "application/dto/configs/SipConfigDto.hpp"
#include "application/dto/configs/DBConfigDto.hpp"
#include "application/dto/configs/MediaConfigDto.hpp"

#include "Util/logger.h"


class ConfigComponent {
private:
    oatpp::base::CommandLineArguments m_cmdArgs;

public:
    ConfigComponent(const oatpp::base::CommandLineArguments &cmdArgs) : m_cmdArgs(cmdArgs) {}

public:
    // 配置组件加载、注册
    OATPP_CREATE_COMPONENT(oatpp::Object<ConfigDto>, config)
    ([this] {
        const char *configPath = m_cmdArgs.getNamedArgumentValue("--profile", nullptr);
        if (configPath == nullptr) {
            configPath = DEV_CONFIG_PATH;  // CMAKE 中读取 CONFIG_PATH
        }

        InfoL << "Server" << "配置文件路径："<< configPath;

        oatpp::String configText = oatpp::String::loadFromFile(configPath);
        if (configText != nullptr) {
            auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
            auto profile      = objectMapper->readFromString<oatpp::Object<ConfigDto>>(configText);
            InfoL<<"Server"<<"成功载入："<< configPath;

            return profile;
        }

        InfoL<< "Server"<< "无法加载配置文件：请使用--profile指定文件路径    "  << configPath;
        throw std::runtime_error("[AppComponent]: Can't load configuration file");
    }());
    // 注册网页配置组件
    OATPP_CREATE_COMPONENT(oatpp::Object<WebConfigDto>, webConfig)
    ([this] {
        OATPP_COMPONENT(oatpp::Object<ConfigDto>, profile);  // 获取配置组件
        InfoL << "Web"<< "网页配置组件加载成功" ;
        return profile->web;
    }());

    // // 注册数据库配置组件
    OATPP_CREATE_COMPONENT(oatpp::Object<DBConfigDto>, dbConfig)
    ([this] {
        OATPP_COMPONENT(oatpp::Object<ConfigDto>, profile);  // 获取配置组件
        InfoL << "DB"<< "数据库配置加载成功";
        return profile->database;
    }());

    // 注册sip服务配置组件
    OATPP_CREATE_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig)
    ([this] {
        OATPP_COMPONENT(oatpp::Object<ConfigDto>, profile);  // 获取配置组件
        InfoL << "sip配置加载成功";
        return profile->sip;
    }());
    // 注册媒体配置组件
    OATPP_CREATE_COMPONENT(oatpp::Object<MediaConfigDto>, mediaConfig)
    ([this] {
        OATPP_COMPONENT(oatpp::Object<ConfigDto>, profile);  // 获取配置组件
        InfoL << "Media"<< "媒体配置组件加载成功";
        return profile->media;
    }());

    // 注册日志配置组件
//     OATPP_CREATE_COMPONENT(oatpp::Object<LogConfigDto>, logConfig)
//     ([this] {
//         OATPP_COMPONENT(oatpp::Object<ConfigDto>, profile);  // 获取配置组件
//         LOGI("DB", "数据库配置组件加载成功");
//         std::shared_ptr<eccom::Logger> logger = std::make_shared<eccom::Logger>(
//             profile->log->save_path, profile->log->max_size_mb, profile->log->preserve_days);
// #if defined(RELEASE)
//         logger->disablePriority(oatpp::base::Logger::PRIORITY_D);
//         logger->disablePriority(oatpp::base::Logger::PRIORITY_V);
// #endif
//         oatpp::base::Environment::setLogger(logger);
//         LOGA("Log", "开始记录日志");
//         return profile->log;
//     }());
};

#endif /* AppComponent_hpp */