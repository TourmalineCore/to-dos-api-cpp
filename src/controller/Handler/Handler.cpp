#include "Handler.h"

using OutgoingResponse = Handler::OutgoingResponse;
using IncomingRequest  = Handler::IncomingRequest;

shared_ptr<OutgoingResponse> 
Handler::handle(const shared_ptr<IncomingRequest>& request) {
  // Link to documentation where you can read about initialization of the DTO object
  // https://oatpp.io/docs/components/dto/#serialize-deserialize
  auto task = Task::createShared();
  task->id = 0;
  task->description = "Develop a new website";
  task->status = false;
  
  // Link to documentation on generating a response using ResponseFactory
  // https://oatpp.io/api/latest/oatpp/web/protocol/http/outgoing/ResponseFactory/#responsefactory
  return ResponseFactory::createResponse(Status::CODE_200, task, m_objectMapper);
};