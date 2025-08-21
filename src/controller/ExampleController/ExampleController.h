#pragma once

#include <thread>
#include <chrono>

#include "../../dto/DTOs.hpp"
#include "../../auth/Authorization/Authorization.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

using namespace oatpp::web::server::handler;

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

/**
 * Sample Api Controller.
 */
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
  ENDPOINT("GET", "/task", getTask) 
  {  
    auto task = Task::createShared();
    task->id = 0;
    task->description = "Develop a new website";
    task->status = false;

    return createDtoResponse(Status::CODE_200, task);
  }

  // Link to documentation where you can read about creating ENDPOINT_INTERCEPTOR
  // https://oatpp.io/api/latest/oatpp/codegen/api_controller/base_define/#endpoint-interceptor
  ENDPOINT_INTERCEPTOR(getTask, exampleInterceptor) 
  {
    OATPP_LOGD("ExampleInterceptor", " Interceptor Action");

    return (this->*intercepted)(request);
  }

  // Link to documentation where you can read about creating BODY_DTO
  // https://oatpp.io/docs/components/api-controller/#request-body-mapping
  ENDPOINT("POST", "/task", postTask, 
    BODY_DTO(oatpp::Object<Task>, taskDto)) 
  {
    if (!taskDto) {
      return createResponse(Status::CODE_400, "Empty body");
    }

    taskDto->status = true;

    return createDtoResponse(Status::CODE_200, taskDto);
  }

  // Link to documentation where you can read about creating QUERY
  // https://oatpp.io/docs/components/api-controller/#query-parameters-mapping
  ENDPOINT("GET", "/query", getQuery,
    QUERY(String, username),
    QUERY(Int32, age)) 
  {
    oatpp::String result = "Query-params: name = " + username + ", age = " + std::to_string(age);
    
    return createResponse(Status::CODE_200, result);
  }

  // Link to documentation where you can read about creating HEADER
  // https://oatpp.io/docs/components/api-controller/#headers-mapping
  ENDPOINT("GET", "/headers", getHeaders, 
    HEADER(String, userAgent, "User-Agent")) 
  {
    oatpp::String result = "User-Agent: " + userAgent;

    return createResponse(Status::CODE_200, result);
  }

  // Link to documentation where you can read about authorization
  // https://oatpp.io/docs/components/api-controller/#authorization-basic
  ENDPOINT("GET", "/secret", secret, 
    AUTHORIZATION(std::shared_ptr<MyAuthorizationObject>, authObject)) 
  {    
    if (authObject) {
      oatpp::String result = "Hello " + authObject->userId + "! Your internal ID is " + std::to_string(authObject->id);

      return createResponse(Status::CODE_200, result);
    }

    return createResponse(Status::CODE_401, "Unauthorized");
  }

  ENDPOINT("GET", "/threads", getThreads) 
  {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    OATPP_LOGD("ENDPOINT", " Controller Action");

    return createResponse(Status::CODE_200, "OK");
  }
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen