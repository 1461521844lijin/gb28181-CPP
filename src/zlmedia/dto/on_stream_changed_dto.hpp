#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace DTO::ZLM
{

class OriginSockDTO : public oatpp::DTO
{
    DTO_INIT(origin_sock_dto, DTO)

    DTO_FIELD_INFO(identifier){
        info->description = "identifier";
    }
    DTO_FIELD(String, identifier);

    DTO_FIELD_INFO(local_ip){
        info->description = "本机ip";
    }
    DTO_FIELD(String, local_ip);

    DTO_FIELD_INFO(local_port){
        info->description = "本机端口";
    }
    DTO_FIELD(Int32, local_port);
    
    DTO_FIELD_INFO(peer_ip){
        info->description = "对端ip";
    }
    DTO_FIELD(String, peer_ip);
    
    DTO_FIELD_INFO(peer_port){
        info->description = "对端port";
    }
    DTO_FIELD(Int32, peer_port);
};

class Track :public oatpp::DTO{
    DTO_INIT(on_stream_changed_dto, DTO)

    DTO_FIELD_INFO(channels){
        info->description = "音频通道数";
    }
    DTO_FIELD(Int32, channels);

    DTO_FIELD_INFO(codec_id){
        info->description = "H264 = 0, H265 = 1, AAC = 2, G711A = 3, G711U = 4";
    }
    DTO_FIELD(Int32, codec_id);

    DTO_FIELD_INFO(codec_id_name){
        info->description = "编码类型名称";
    }
    DTO_FIELD(String, codec_id_name);

    DTO_FIELD_INFO(codec_type){
        info->description = "Video = 0, Audio = 1";
    }
    DTO_FIELD(Int32, codec_type);

    DTO_FIELD_INFO(ready){
        info->description = "轨道是否准备就绪";
    }
    DTO_FIELD(Boolean, ready);

    DTO_FIELD_INFO(sample_bit){
        info->description = "音频采样位数";
    }
    DTO_FIELD(Int32, sample_bit);

    DTO_FIELD_INFO(sample_rate){
        info->description = "音频采样率";
    }
    DTO_FIELD(Int32, sample_rate);

    DTO_FIELD_INFO(fps){
        info->description = "视频fps";
    }
    DTO_FIELD(Int32, fps);

    DTO_FIELD_INFO(height){
        info->description = "视频高";
    }
    DTO_FIELD(Int32, height);

    DTO_FIELD_INFO(width){
        info->description = "视频宽";
    }
    DTO_FIELD(Int32, width);

    DTO_FIELD_INFO(ready){
        info->description = "轨道是否准备就绪";
    }
    DTO_FIELD(Boolean, ready);

}

class OnStreamChangedDTO : public oatpp::DTO
{
    DTO_INIT(on_stream_changed_dto, DTO)

    DTO_FIELD_INFO(regist){
        info->description = "注册还是注销标识";
    }
    DTO_FIELD(Boolean, regist);

    DTO_FIELD_INFO(aliveSecond){
        info->description = "存活时间，单位秒";
    }
    DTO_FIELD(Int32, aliveSecond);

    DTO_FIELD_INFO(app){
        info->description = "应用名";
    }
    DTO_FIELD(String, app);

    DTO_FIELD_INFO(bytesSpeed){
        info->description = "数据产生速度，单位byte/s";
    }
    DTO_FIELD(Int32, bytesSpeed);

    DTO_FIELD_INFO(createStamp){
        info->description = "GMT unix系统时间戳，单位秒";
    }
    DTO_FIELD(Int32, createStamp);

    DTO_FIELD_INFO(mediaServerId){
        info->description = "服务器id";
    }
    DTO_FIELD(String, mediaServerId);

    DTO_FIELD_INFO(originSock){
        info->description = "原始socket信息";
    }
    DTO_FIELD(OriginSockDTO, originSock);

    DTO_FIELD_INFO(originType){
        info->description = "产生源类型，包括 unknown = 0,rtmp_push=1,rtsp_push=2,rtp_push=3,pull=4,ffmpeg_pull=5,mp4_vod=6,device_chn=7,rtc_push=8";
    }
    DTO_FIELD(Int32, originType);

    DTO_FIELD_INFO(originTypeStr){
        info->description = "产生源类型字符串";
    }
    DTO_FIELD(String, originTypeStr);

    DTO_FIELD_INFO(originUrl){
        info->description = "产生源的url";
    }
    DTO_FIELD(String, originUrl);

    DTO_FIELD_INFO(readerCount){
        info->description = "本协议观看人数";
    }
    DTO_FIELD(Int32, readerCount);

    DTO_FIELD_INFO(schema){
        info->description = "协议";
    }
    DTO_FIELD(String, schema);

    DTO_FIELD_INFO(stream){
        info->description = "流id";
    }
    DTO_FIELD(String, stream);

    DTO_FIELD_INFO(totalReaderCount){
        info->description = "观看总人数，包括hls/rtsp/rtmp/http-flv/ws-flv/rtc";
    }
    DTO_FIELD(Int32, totalReaderCount);


    DTO_FIELD_INFO(tracks){
        info->description = "轨道信息";
    }
    DTO_FIELD(Vector<Track>, tracks);

    DTO_FIELD_INFO(vhost){
        info->description = "流虚拟主机";
    }
    DTO_FIELD(String, vhost);
};
    
} // namespace dto::zlm





