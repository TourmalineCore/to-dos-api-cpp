#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"

class RouterInterceptor : public oatpp::web::server::interceptor::RequestInterceptor {
public:
  std::shared_ptr<oatpp::web::protocol::http::outgoing::Response>
  intercept(const std::shared_ptr<oatpp::web::protocol::http::incoming::Request>& request) override;
};