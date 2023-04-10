#pragma once 

#include "zlmedia/dto/on_server_keepalive_dto.hpp"
#include "zlmedia/dto/on_stream_changed_dto.hpp"


namespace ZLM
{


oatpp::Object<DTO::ZLM::ResponseDto>  on_server_keepalive_api(const oatpp::Object<DTO::ZLM::OnServerKeepaliveDto>& onServerKeepaliveTiem);

oatpp::Object<DTO::ZLM::ResponseDto>  on_stream_changed_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO>& onStreamChangedTiem);





    
} // namespace ZLM
