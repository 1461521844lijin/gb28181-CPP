
#ifndef POSTGRESQL_DATABASECOMPONENT_HPP
#define POSTGRESQL_DATABASECOMPONENT_HPP

class DatabaseComponent {
public:

  /**
   * PatientDB
   * 创建数据库连接组件
   */
  // OATPP_CREATE_COMPONENT(std::shared_ptr<PatientDB>, patientDb)([] {
  //   OATPP_COMPONENT(oatpp::Object<ConfigDto>, config); // 获取配置组件
  //   /* 创建数据库连接 */
  //   auto connectionProvider = std::make_shared<oatpp::postgresql::ConnectionProvider>(config->dbConnectionString);
  //   /* 创建连接池 */
  //   auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(connectionProvider,
  //                                                                         100 /* 最大连接数 */,
  //                                                                         std::chrono::seconds(5) /* connection TTL */);
  //   /* 创建连接访问句柄 */
  //   auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);
  //   /* 创建并返回客户端 */
  //   return std::make_shared<PatientDB>(executor);
  // }());

};

#endif //POSTGRESQL_DATABASECOMPONENT_HPP
