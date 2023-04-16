#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ZLM {

class SSRCInfo {
public:
    typedef std::shared_ptr<SSRCInfo> ptr;

    SSRCInfo(int port, const std::string &ssrc, const std::string &stream)
        : m_port(port), m_ssrc(ssrc), m_strema(stream) {}

private:
    int         m_port;
    std::string m_ssrc;
    std::string m_strema;

public:
    int                getPort() const;
    void               setPort(int port);
    const std::string &getSsrc() const;
    void               setSsrc(const std::string &ssrc);
    const std::string &getStrema() const;
    void               setStrema(const std::string &strema);
};

class SSRCConfig {
public:
    typedef std::shared_ptr<SSRCConfig> ptr;

    SSRCConfig() = default;
    SSRCConfig(const std::string        &mediaServerId,
               const std::string        &sipDomain);

private:
    std::string m_mediaServerId;  // 媒体服务器ID
    std::string m_ssrcPrefix;     // ssrc前缀

    std::vector<std::string> m_ssrcIsUsed;  // 已经使用的ssrc
    std::vector<std::string> m_ssrcUnused;  // 未使用的ssrc

    // TODO: 未实现  需要实现ssrc的回收，在call_session回收后，ssrc回收

public:
    std::string getPlaySsrc();      // 获取播放ssrc
    std::string getPlayBackSsrc();  // 获取回放ssrc

    void releaseSsrc(const std::string &ssrc);  // 释放ssrc
    bool checkSsrc(const std::string &ssrc);    // 检查ssrc是否可用

    std::string getSsrcPrefix() const;
    void        setSsrcPrefix(const std::string &ssrcPrefix);
    std::string getMediaServerId() const;
    void        setMediaServerId(const std::string &mediaServerId);

private:
    std::string getSN();  // 获取后四位数sn，随机数
};

}  // namespace GB28181
