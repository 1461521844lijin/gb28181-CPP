#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace DTO::ZLM {

//   "Buffer" : 12,
//   "BufferLikeString" : 0,
//   "BufferList" : 0,
//   "BufferRaw" : 12,
//   "Frame" : 0,
//   "FrameImp" : 0,
//   "MediaSource" : 0,
//   "MultiMediaSourceMuxer" : 0,
//   "RtmpPacket" : 0,
//   "RtpPacket" : 0,
//   "Socket" : 108,
//   "TcpClient" : 0,
//   "TcpServer" : 96,
//   "TcpSession" : 0,
//   "UdpServer" : 12,
//   "UdpSession" : 0

class DataDto : public oatpp::DTO {
    DTO_INIT(DataDto, DTO)

    DTO_FIELD(Int32, Buffer);
    DTO_FIELD(Int32, BufferLikeString);
    DTO_FIELD(Int32, BufferList);
    DTO_FIELD(Int32, BufferRaw);
    DTO_FIELD(Int32, Frame);
    DTO_FIELD(Int32, FrameImp);
    DTO_FIELD(Int32, MediaSource);
    DTO_FIELD(Int32, MultiMediaSourceMuxer);
    DTO_FIELD(Int32, RtmpPacket);
    DTO_FIELD(Int32, RtpPacket);
    DTO_FIELD(Int32, Socket);
    DTO_FIELD(Int32, TcpClient);
    DTO_FIELD(Int32, TcpServer);
    DTO_FIELD(Int32, TcpSession);
    DTO_FIELD(Int32, UdpServer);
    DTO_FIELD(Int32, UdpSession);
};

class OnServerKeepaliveDto : public oatpp::DTO {
    DTO_INIT(OnServerKeepaliveDto, DTO)

    DTO_FIELD_INFO(data) {
        info->description = "data";
    }
    DTO_FIELD(Object<DataDto>, data);

    DTO_FIELD_INFO(mediaServerId) {
        info->description = "区分zlm服务的唯一id";
    }
    DTO_FIELD(String, mediaServerId);
};


class ResponseDto : public oatpp::DTO {
    DTO_INIT(ResponseDto, DTO)

    DTO_FIELD_INFO(code) {
        info->description = "code";
    }
    DTO_FIELD(Int32, code);

    DTO_FIELD_INFO(msg) {
        info->description = "msg";
    }
    DTO_FIELD(String, msg);

    DTO_FIELD_INFO(close) {
        info->description = "close";
    }
    DTO_FIELD(Boolean, close);
};


} // namespace DTO::ZLM


