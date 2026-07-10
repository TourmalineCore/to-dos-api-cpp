#pragma once

#include <drogon/HttpResponse.h>

#include <exception>

class ExceptionResponseHandler
{
public:
    [[nodiscard]] static drogon::HttpResponsePtr handle(const std::string& status, const std::string& message, drogon::HttpStatusCode status_code);
};