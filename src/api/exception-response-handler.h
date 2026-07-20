#pragma once

#include <drogon/HttpResponse.h>

#include <exception>

class ExceptionResponseHandler
{
public:
    /// @brief Creates a JSON HTTP error response with the specified status and message.
    /// @param status Status value included in the JSON response body.
    /// @param message Message included in the JSON response body.
    /// @param status_code HTTP status code returned to the client.
    /// @return JSON HTTP response.
    [[nodiscard]] static drogon::HttpResponsePtr handle(const std::string& status, const std::string& message, drogon::HttpStatusCode status_code);

    /// @brief Handles an unexpected exception and creates an internal server error response.
    /// @param exception Exception caught while handling an HTTP request.
    /// @return HTTP 500 JSON response.
    [[nodiscard]] static drogon::HttpResponsePtr handle(const std::exception& exception);
};