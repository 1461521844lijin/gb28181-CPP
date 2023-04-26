#pragma once

#include <memory>
#include <string>

namespace Tools
{

static inline unsigned char FromHex(unsigned char x) {
    unsigned char y;
    if (x >= 'A' && x <= 'Z')
        y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z')
        y = x - 'a' + 10;
    else if (x >= '0' && x <= '9')
        y = x - '0';
    else
        return 0;
    return y;
}

static inline unsigned char ToHex(unsigned char x) {
    return x > 9 ? x + 55 : x + 48;
}

static inline std::string UrlDecode(const std::string &str) {
    std::string strTemp;
    size_t      length = str.length();
    for (size_t i = 0; i < length; i++) {
        if (str[i] == '+')
            strTemp += ' ';
        else if (str[i] == '%') {
            if (i + 2 >= length)
                break;
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low  = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        } else
            strTemp += str[i];
    }
    return strTemp;
}

static inline std::string UrlEncode(const std::string &str) {
    std::string strTemp;
    size_t      length = str.length();
    for (size_t i = 0; i < length; i++) {
        if (isalnum((unsigned char)str[i]) || (str[i] == '-') || (str[i] == '_') ||
            (str[i] == '.') || (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}


static inline std::map<std::string, std::string> Parse_param(std::string& params){
    std::map<std::string, std::string> param_map;
    std::string key;
    std::string value;
    std::string::size_type pos = 0;
    std::string::size_type pos2 = 0;
    while (pos < params.size()) {
        pos2 = params.find('=', pos);
        if (pos2 == std::string::npos) {
            break;
        }
        key = params.substr(pos, pos2 - pos);
        pos = pos2 + 1;
        pos2 = params.find('&', pos);
        if (pos2 == std::string::npos) {
            value = params.substr(pos, params.size() - pos);
            param_map[key] = value;
            break;
        }
        value = params.substr(pos, pos2 - pos);
        param_map[key] = value;
        pos = pos2 + 1;
    }
    return param_map;
}



} // namespace Tools