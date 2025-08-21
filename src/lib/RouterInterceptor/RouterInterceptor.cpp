#include "RouterInterceptor.h"

std::shared_ptr<oatpp::web::protocol::http::outgoing::Response>
RouterInterceptor::intercept(const std::shared_ptr<oatpp::web::protocol::http::incoming::Request>& request) {
  OATPP_LOGD("RouterInterceptor", " Intercept request");

  return nullptr;
};