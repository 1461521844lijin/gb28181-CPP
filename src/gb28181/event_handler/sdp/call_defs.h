/*
**	********************************************************************************
**
**	File		: call_defs.h
**	Description	: 
**	Modify		: 2020/3/4		zhangqiang		Create the file
**	********************************************************************************
*/
#pragma once

#include <string>
#include <map>
#include "Util/logger.h"

using namespace std;

namespace GB28181 {

enum media_operate_type_e
{
    MOT_UNKNOWN  =0,
    MOT_PLAY,
    MOT_DOWNLOAD,
    MOT_PLAYBACK,
    MOT_TALK,
};

struct sdp_description_t
{
    ///< v=0
    // 版本号
    string      v_version;

    ///< o=34020000002000000001 B8975BC37429408E83BBAB32535D07B2 0 IN IP4 172.18.3.203
    // 
    string      o_username;         ///< owner/creator
    string      o_sessid;           ///< session ID
    string      o_sess_version;     ///< session version
    string      o_nettype;          ///< network type
    string      o_addrtype;         ///< address type
    string      o_addr;             ///< address

    ///< s=Play
    // 会话名称
    string      s_sess_name;        ///< media_operate_type_e

    ///< u=34020000001320000002
    string      u_uri;

    ///< c=IN IP4 172.18.3.204
    // 
    string      c_nettype;      ///< network type
    string      c_addrtype;     ///< address type
    string      c_addr;         ///< address

    ///< t= 0 0
    // 
    string      t_startime;
    string      t_endtime;

    ///< m=video 38930 RTP/AVP 96 98 97
    // ??????? ???????????????????????????????????????m=??????????????m=????????
    string      m_media;            ///< media type  ??"audio", ??video??,??application??????????????, ??data????????????????????? ??"control"???????????????????
    string      m_port;             /// ????��???????????
    string      m_tmode;            ///< TCP(TCP/RTP/AVP) or UDP??RTP/AVP??media transmit mode
    string      m_payloadtype;      ///< payload type 

    ///< a=recvonly
    ///< a=rtpmap:96 PS/90000
    map<string, string> a_attrimap; ///< a???  ????????????????????

    ///< y=0200003000
    string      y_ssrc;

    ///< f=v/1/5/3///a///
    string      f_media_desc;

    void print() {
        InfoL << "o_username: " << o_username;
        InfoL << "o_sessid: " << o_sessid;
        InfoL << "o_sess_version: " << o_sess_version;
        InfoL << "o_nettype: " << o_nettype;
        InfoL << "o_addrtype: " << o_addrtype;
        InfoL << "o_addr: " << o_addr;
        InfoL << "s_sess_name: " << s_sess_name;
        InfoL << "u_uri: " << u_uri;
        InfoL << "c_nettype: " << c_nettype;
        InfoL << "c_addrtype: " << c_addrtype;
        InfoL << "c_addr: " << c_addr;
        InfoL << "t_startime: " << t_startime;
        InfoL << "t_endtime: " << t_endtime;
        InfoL << "m_media: " << m_media;
        InfoL << "m_port: " << m_port;
        InfoL << "m_tmode: " << m_tmode;
        InfoL << "m_payloadtype: " << m_payloadtype;
        InfoL << "y_ssrc: " << y_ssrc;
        InfoL << "f_media_desc: " << f_media_desc;

        for (auto a : a_attrimap) {
            InfoL << "attri key: " << a.first << ", value: " << a.second;
        }
    }

    std::string to_string(){
        
    }

    



};

}
