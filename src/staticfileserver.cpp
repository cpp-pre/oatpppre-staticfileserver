#include "StaticFileServerComponent.hpp"

#include "StaticFilesController.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run() {
  
  StaticFileServerComponent components; // Create scope Environment components
  
  /* create ApiControllers and add endpoints to router */
  
  auto router = components.httpRouter.getObject();
  
  auto controller = StaticFilesController::createShared();
  controller->addEndpointsToRouter(router);

  router->route("GET", "/*", std::make_shared<StaticFilesHandler>());

  
  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* create server */
  oatpp::network::Server server(connectionProvider, connectionHandler);
  
  OATPP_LOGD("Server", "Running on port %s...", connectionProvider->getProperty("port").toString()->c_str());
  
  server.run();

}

/**
 *  main
 */
int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run();

  oatpp::base::Environment::destroy();
  
  return 0;
}
