#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"


#include "application/dto/StatusDto.hpp"
#include "application/dto/PlayDto.hpp"

#include "application/service/PTZOperator.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class PTZController : public oatpp::web::server::api::ApiController {
public:
    PTZController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) {}
    static std::shared_ptr<PTZController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) 
    ) {
        return std::make_shared<PTZController>(objectMapper);
    }

public:

    ENDPOINT_INFO(device_ptz_ctl) {
        info->summary = "国标设备ptz控制相关操作";
        info->addTag("PTZ");
        info->addConsumes<Object<PtzDto>>("application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");
    }
    ENDPOINT("GET", "/api/ptz/control/{deviceId}/{channelId}", device_ptz_ctl, PATH(String, deviceId), PATH(String, channelId), QUERY(String, command), QUERY(Int32, speed)) {
    
        return createDtoResponse(Status::CODE_200,  OP::ptz_ctl(deviceId, channelId, command, speed));
    }





};