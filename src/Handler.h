#pragma once

// Link to documentation where you can read about the types inside HttpRequestHandler
// https://oatpp.io/api/latest/oatpp/web/server/HttpRequestHandler/
#include "oatpp/web/server/HttpRequestHandler.hpp"

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

using namespace std;

// Link to documentation where you can read about DTO (Data Transfer Object)
// https://oatpp.io/docs/components/dto/
#include OATPP_CODEGEN_BEGIN(DTO)

class Task : public oatpp::DTO {

  // Link to documentation where you can read about Codegen macoro
  // https://oatpp.io/api/latest/oatpp/codegen/dto/base_define/
  DTO_INIT(Task, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, description);
  DTO_FIELD(Boolean, status);

};

#include OATPP_CODEGEN_END(DTO)

class Handler : public oatpp::web::server::HttpRequestHandler {
public:
  using ObjectMapper = oatpp::data::mapping::ObjectMapper;

  /**
   * Constructor with object mapper.
   * @param objectMapper - object mapper used to serialize objects.
   */
  Handler(const shared_ptr<ObjectMapper>& objectMapper);

  using OutgoingResponse = oatpp::web::server::HttpRequestHandler::OutgoingResponse;
  using IncomingRequest  = oatpp::web::server::HttpRequestHandler::IncomingRequest;

  shared_ptr<OutgoingResponse> handle(const shared_ptr<IncomingRequest>& request) override;
private:
  shared_ptr<ObjectMapper> m_objectMapper;
};