#ifndef ServiceComponent_h
#define ServiceComponent_h

#include "ErrorHandler.hpp"
#include "../dto/configs/WebConfigDto.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"

class ServiceComponent {
public:
    /**
     *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's
     * API 创建 ObjectMapper 组件，用于序列化/反序列化 DTOs
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)
    ([] {
        auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        mapper->getSerializer()->getConfig()->useBeautifier = true;
        mapper->getSerializer()->getConfig()->escapeFlags   = 0;
        return mapper;
    }());

    /**
     *  Create ConnectionProvider component which listens on the port
     * 创建 ConnectionProvider 组件，监听端口
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                           serverConnectionProvider)
    ([] {
        OATPP_COMPONENT(oatpp::Object<WebConfigDto>, webConfig);  // Get config component
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
            {webConfig->host, webConfig->port, oatpp::network::Address::IP_4});
    }());

    /**
     *  Create Router component
     * 创建 Router 组件
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
    ([] { return oatpp::web::server::HttpRouter::createShared(); }());

    /**
     *  Create ConnectionHandler component which uses Router component to route
     * requests 创建 ConnectionHandler 组件，使用 Router 组件来路由请求
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                           serverConnectionHandler)
    ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                        router);  // get Router component
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);  // get ObjectMapper component

        auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
        connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(objectMapper));
        return connectionHandler;
    }());
};

#endif /* ServiceComponent_h */