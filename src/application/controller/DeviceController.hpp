#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"


#include "application/dto/StatusDto.hpp"
#include "application/dto/PlayDto.hpp"

#include "application/service/DeviceOperator.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class DeviceController : public oatpp::web::server::api::ApiController {
public:
    DeviceController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}

public:
    static std::shared_ptr<DeviceController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>,
                                                                            objectMapper)  // Inject objectMapper component here as default parameter
    ) {
        return std::make_shared<DeviceController>(objectMapper);
    }

    ENDPOINT_INFO(deviceOP) {
        info->summary = "国标设备点播相关操作";
        info->addTag("Device");
        info->addConsumes<Object<PlayDto>>("application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST", "/api/device", deviceOP, BODY_DTO(Object<PlayDto>, playDto)) {
    
        return createDtoResponse(Status::CODE_200,  Web::do_taks(playDto));
    }

    ENDPOINT_INFO(devicePTZ) {
        info->summary = "国标设备ptz控制相关操作";
        info->addTag("Device");
        info->addConsumes<Object<PtzDto>>("application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("POST", "/api/device/ptz", devicePTZ, BODY_DTO(Object<PtzDto>, ptzDto)) {
    
        return createDtoResponse(Status::CODE_200,  Web::ptz_ctl(ptzDto));
    }



};