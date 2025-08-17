#pragma once

#include "../../dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

using namespace std;

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
  {}
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
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen