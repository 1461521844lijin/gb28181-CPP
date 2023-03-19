#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)

class StatusDto : public oatpp::DTO {

    DTO_INIT(StatusDto, DTO)

    DTO_FIELD_INFO(errorCode) {
        info->description = "Status code";
    };
    DTO_FIELD(Int32, errorCode);

    DTO_FIELD_INFO(errorMsg) {
        info->description = "Status message";
    };
    DTO_FIELD(String, errorMsg);

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