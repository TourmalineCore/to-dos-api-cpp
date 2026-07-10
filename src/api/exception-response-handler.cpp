#include "exception-response-handler.h"

#include <drogon/drogon.h>

drogon::HttpResponsePtr ExceptionResponseHandler::handle(const std::string& status, const std::string& message, drogon::HttpStatusCode status_code)
{
    Json::Value responseBody;
    responseBody["status"] = status;
    responseBody["message"] = message;

    auto response = drogon::HttpResponse::newHttpJsonResponse(responseBody);
    response->setStatusCode(status_code);

    return response;
}
