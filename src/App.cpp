

// #include "controller/UserController.hpp"
#include "Util/logger.h"
#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"
#include "utils/System.h"

#include <signal.h>
#include <unistd.h>
#include <iostream>

#include "gb28181/sip_server.h"

#include "application/oatppComponents//ServiceComponent.hpp"
#include "application/oatppComponents/ConfigComponent.hpp"
#include "application/oatppComponents/DatabaseComponent.hpp"
#include "application/oatppComponents/SwaggerComponent.hpp"
#include "oatpp/core/base/CommandLineArguments.hpp"

#include "application/controller/PtzController.hpp"
#include "application/controller/PlayController.hpp"
#include "application/controller/RecordController.hpp"

#include "zlmedia/web_hook/web_hook_controller.hpp"

    
#include "Poller/EventPoller.h"
using namespace toolkit;
void run_sip(){

    // GB28181::SipServer svr;
    OATPP_COMPONENT(oatpp::Object<SipConfigDto>, sipConfig);

    GB28181::g_SipServer::GetInstance()->SetLocalConfig(sipConfig->sipId,sipConfig->sipHost,sipConfig->sipPort);
    GB28181::g_SipServer::GetInstance()->Init();
    GB28181::g_SipServer::GetInstance()->Start(sipConfig->sipPa);
}


void run_oatpp() {
    
    // DatabaseComponent databaseComponent;

    /* Get router component */

    // auto router =  serviceComponent.httpRouter.getObject();
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    oatpp::web::server::api::Endpoints docEndpoints;


    // 将接口添加到路由器和swagger中
    router->addController(PTZController::createShared());
    docEndpoints.append(router->addController(PTZController::createShared())->getEndpoints());
    router->addController(PlayController::createShared());
    docEndpoints.append(router->addController(PlayController::createShared())->getEndpoints());
    router->addController(ZLM::ZlmWebHookController::createShared());
    docEndpoints.append(router->addController(ZLM::ZlmWebHookController::createShared())->getEndpoints());
    router->addController(RecordController::createShared());
    docEndpoints.append(router->addController(RecordController::createShared())->getEndpoints());


    router->addController(oatpp::swagger::Controller::createShared(docEndpoints));
    /* Get connection handler component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    /* Get connection provider component */
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
    /* create server */
    oatpp::network::Server server(connectionProvider, connectionHandler);
    OATPP_LOGD("Server", "Running on port %s...",
               connectionProvider->getProperty("port").toString()->c_str());
  
    server.run();
}

int start_main(int argc, const char *argv[]) {
    // if (FLAGS_d) {
    //     pid_t pid                   = getpid();  // 父进程pid
    //     bool  kill_parent_if_failed = true;
    //     // 启动守护进程
    //     System::startDaemon(kill_parent_if_failed);
    //     // 开启崩溃捕获等
    //     System::systemSetup();
    // }

    Logger::Instance().add(std::make_shared<ConsoleChannel>("ConsoleChannel", LogLevel(1)));
    
    oatpp::base::Environment::init();
    ConfigComponent   configComponent(oatpp::base::CommandLineArguments(argc, argv));
    ServiceComponent  serviceComponent;
    SwaggerComponent  swaggerComponent;


    toolkit::EventPollerPool::setPoolSize(10);

    run_sip();
    run_oatpp();

    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";

    oatpp::base::Environment::destroy();

    // 休眠1秒再退出，防止资源释放顺序错误
    WarnL << "程序退出中,请等待...";
    sleep(1);
    WarnL << "程序退出完毕!";
    return 0;
}

/**
 *  main
 */
int main(int argc, const char *argv[]) {
    return start_main(argc, argv);
}
