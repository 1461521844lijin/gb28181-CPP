#pragma once 

#include "zlmedia/dto/on_server_keepalive_dto.hpp"
#include "zlmedia/dto/on_stream_changed_dto.hpp"
#include "zlmedia/dto/on_publish_dto.hpp"


namespace ZLM
{


oatpp::Object<DTO::ZLM::ResponseDto>  on_server_keepalive_api(const oatpp::Object<DTO::ZLM::OnServerKeepaliveDto>& onServerKeepaliveItem);

oatpp::Object<DTO::ZLM::ResponseDto>  on_stream_changed_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO>& onStreamChangedItem);

oatpp::Object<DTO::ZLM::ResponseDto>  on_stream_none_reader_api(const oatpp::Object<DTO::ZLM::OnStreamChangedDTO>& onStreamChangedItem);

oatpp::Object<DTO::ZLM::ResponseDto>  on_publish_api(const oatpp::Object<DTO::ZLM::OnPublishDTO>& onPublishItem);


oatpp::Object<DTO::ZLM::ResponseDto>  on_play_api(const oatpp::Object<DTO::ZLM::OnPublishDTO>& onPublishItem);



    
} // namespace ZLM
