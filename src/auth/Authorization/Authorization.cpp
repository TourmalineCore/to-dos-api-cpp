#include "Authorization.h"

std::shared_ptr<oatpp::web::server::handler::AuthorizationObject> Authorization::authorize(
    const oatpp::String& userId,
    const oatpp::String& password) {

  if (checkFunction()) {
    return std::make_shared<MyAuthorizationObject>(0, userId);
  }

  return nullptr;
}

bool Authorization::checkFunction() {
  return true;
}
