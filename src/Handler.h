#pragma once

// Link to documentation where you can read about the types inside HttpRequestHandler
// https://oatpp.io/api/latest/oatpp/web/server/HttpRequestHandler/
#include "oatpp/web/server/HttpRequestHandler.hpp"

using namespace std;

class Handler : public oatpp::web::server::HttpRequestHandler {
public:
  using OutgoingResponse = oatpp::web::server::HttpRequestHandler::OutgoingResponse;
  using IncomingRequest  = oatpp::web::server::HttpRequestHandler::IncomingRequest;

  shared_ptr<OutgoingResponse> handle(const shared_ptr<IncomingRequest>& request) override;
};