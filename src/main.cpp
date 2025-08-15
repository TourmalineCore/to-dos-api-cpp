#include "to-dos-api.h"
#include "Handler.h"

#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

void run() {

  /* Create json object mapper */
  auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

  /* Create Router for HTTP requests routing */
  auto router = oatpp::web::server::HttpRouter::createShared();

  /* Route GET - "/task" requests to Handler */
  router->route("GET", "/task", std::make_shared<Handler>(objectMapper));

  /* Create HTTP connection handler with router */
  auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

  /* Create TCP connection provider */
  auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("to-dos-cpp-oat-exp", "Server running on port %s", connectionProvider->getProperty("port").getData());

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
