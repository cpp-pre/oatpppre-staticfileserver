#include <oatpppre/StaticFilesHandler.hpp>
#include <oatpp/network/Server.hpp>
#include <iostream>

#include "StaticFileServerComponent.hpp"

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  // Create typical oatpp scope Environment components
  StaticFileServerComponent components; 
  
  auto router = components.httpRouter.getObject();
  
  oatpppre::StaticFilesHandler::mountAtRoute(router, "/files/*", "."); // Add the static file handler
  
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);
  oatpp::network::Server server(connectionProvider, connectionHandler);
  
  OATPP_LOGD("Server", "Running on port %s...", connectionProvider->getProperty("port").toString()->c_str());
  
  server.run();

  oatpp::base::Environment::destroy();
  
  return 0;
}
