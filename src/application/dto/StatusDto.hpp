#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class StatusDto : public oatpp::DTO {

public:
    DTO_INIT(StatusDto, DTO)

    DTO_FIELD_INFO(code) {
        info->description = "返回码 0成功, -1失败";
    };
    DTO_FIELD(Int32, code);

    DTO_FIELD_INFO(msg) {
        info->description = "返回消息内容";
    };
    DTO_FIELD(String, msg);

};


class taskData : public oatpp::DTO{

    DTO_INIT(taskData, DTO)

    DTO_FIELD_INFO(taskId) {
        info->description = "Task ID";
        info->required = true;
    };
    DTO_FIELD(String, taskId);

    DTO_FIELD_INFO(taskStatus) {
        info->description = "Task status";
        info->required = true;
    };
    DTO_FIELD(String, taskStatus);


};


class taskDataResult : public StatusDto{

    DTO_INIT(taskDataResult, StatusDto)

    DTO_FIELD_INFO(data) {
        info->description = "Task data";
        info->required = true;
    };
    DTO_FIELD(List<Object<taskData>>, data);

};




#include OATPP_CODEGEN_END(DTO)