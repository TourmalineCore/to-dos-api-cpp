#include "to-dos-api.h"
#include "AppComponent.hpp"
#include "controller/ExampleController/ExampleController.h"

#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

using namespace std;

void run() {

  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create ExampleController and add all of its endpoints to router */
  auto exampleController = make_shared<ExampleController>();
  router->addController(exampleController);

  /* Get connection handler component */
  OATPP_COMPONENT(shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("to-dos-cpp-oat-exp",
           "Server running on port %s",
           connectionProvider->getProperty("port").toString()->c_str());

  /* Run server */
  server.run();
}


int main() {

  /* Init oatpp Environment */
  oatpp::base::Environment::init();

  /* Run App */
  run();

  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();

  return 0;

}
