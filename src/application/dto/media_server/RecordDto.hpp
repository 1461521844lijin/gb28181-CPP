#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace DTO::GETWAY {


// secret	Y	api操作密钥(配置文件配置)，如果操作ip是127.0.0.1，则不需要此参数	string
// type	Y	0为hls，1为mp4	0/1
// vhost	Y	虚拟主机，例如__defaultVhost__	string
// app	Y	应用名，例如 live	string
// stream	Y	流id，例如 obs	string
// customized_path	N	录像保存目录	string
// max_second	N	mp4录像切片时间大小,单位秒，置0则采用配置项	int


class RecordDto : public oatpp::DTO {
    DTO_INIT(RecordDto, DTO)

    DTO_FIELD_INFO(type) {
        info->description = "0为hls，1为mp4";
    }
    DTO_FIELD(Int32, type) = 1;

    // DTO_FIELD_INFO(vhost) {
    //     info->description = "虚拟主机，例如__defaultVhost__";
    // }
    // DTO_FIELD(String, vhost);

    DTO_FIELD_INFO(app) {
        info->description = "应用名，例如 live";
    }
    DTO_FIELD(String, app);

    DTO_FIELD_INFO(stream) {
        info->description = "流id，例如 obs";
    }
    DTO_FIELD(String, stream) = "";

    DTO_FIELD_INFO(max_second) {
        info->description = "mp4录像切片时间大小,单位秒，置0则采用配置项";
    }
    DTO_FIELD(Int32, max_second) = 0;

    
};


}