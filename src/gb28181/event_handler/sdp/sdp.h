/*
**	********************************************************************************
**
**	File		: sdp.h
**	Description	: 
**	Modify		: 2020/3/4		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include "call_defs.h"


namespace GB28181 {

class SdpParser
{
public:
    SdpParser();
    ~SdpParser();

    /**
     * @brief 解析SDP
     * 
     * @param sdp SDP
     * @param sdp_info SDP信息
     * @return int 
     */
    int ParseSdp(const char *buf, sdp_description_t &sdp_desc);

    /**
     * @brief 生成SDP  待实现
     * 
     * @param sdp_info SDP信息
     * @param sdp SDP
     * @return int 
     */
    int AssembleSdp(string &sdp, const sdp_description_t &sdp_desc);
};

}
