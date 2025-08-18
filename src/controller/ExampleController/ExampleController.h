#pragma once

#include "../../dto/DTOs.hpp"
#include "../../auth/Authorization/Authorization.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

using namespace std;
using namespace oatpp::web::server::handler;

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

/**
 * Sample Api Controller.
 */
// Link to documentation where you can read about authorization
// https://oatpp.io/docs/components/api-controller/#authorization-basic
class ExampleController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  ExampleController(OATPP_COMPONENT(shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {
    setDefaultAuthorizationHandler(std::make_shared<Authorization>("MyRealm"));
  }

public:
  // Link to documentation where you can read about creating ENDPOINT
  // https://oatpp.io/api/latest/oatpp/codegen/api_controller/base_define/#endpoint
  ENDPOINT("GET", "/task", root) {
    auto task = Task::createShared();
    task->id = 0;
    task->description = "Develop a new website";
    task->status = false;

    return createDtoResponse(Status::CODE_200, task);
  }

  ENDPOINT("POST", "/task", createTask, BODY_DTO(oatpp::Object<Task>, taskDto)) {
    if (!taskDto) {
      return createResponse(Status::CODE_400, "Empty body");
    }

    taskDto->status = true;

    return createDtoResponse(Status::CODE_200, taskDto);
  }

  ENDPOINT("GET", "/query", getTasks,
         QUERY(String, name),
         QUERY(Int32, count)) {

    auto result = "Query: name = " + name + ", count = " + to_string(count);
    
    return createResponse(Status::CODE_200, result);
  }

  ENDPOINT("GET", "/headers", headers, REQUEST(std::shared_ptr<IncomingRequest>, request)) {
    auto userAgent = request->getHeader("User-Agent");
    auto custom = request->getHeader("X-Custom-Header");

    oatpp::String result = "User-Agent: " + (userAgent ? userAgent : "none") +
                            "\nX-Custom-Header: " + (custom ? custom : "none");

    return createResponse(Status::CODE_200, result);
  }

  ENDPOINT("GET", "/secret", secret, 
    AUTHORIZATION(std::shared_ptr<MyAuthorizationObject>, authObject)
  ) {    
    if (authObject) {
      return createResponse(Status::CODE_200, "Hello " + authObject->userId + 
        "! Your internal ID is " + std::to_string(authObject->id));
    }

    return createResponse(Status::CODE_401, "Unauthorized");
  }
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen