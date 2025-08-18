#pragma once

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"

class MyAuthorizationObject : public oatpp::web::server::handler::AuthorizationObject {
 public:
  MyAuthorizationObject(v_int64 pId, const oatpp::String& pUser)
  : id(pId), userId(pUser)
  {}

  v_int64 id;
  oatpp::String userId;
};

class Authorization : public oatpp::web::server::handler::BasicAuthorizationHandler {
public:
  Authorization(const oatpp::String &realm) : BasicAuthorizationHandler(realm) {}

  std::shared_ptr<AuthorizationObject> authorize(
    const oatpp::String& userId, 
    const oatpp::String& password) override;
private:
  bool checkFunction();
};
