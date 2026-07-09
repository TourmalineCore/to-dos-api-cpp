#pragma once

#include <drogon/HttpResponse.h>
#include <json/value.h>
#include <memory>
#include <optional>
#include <string>

struct HealthcheckResponse
{
    bool isHealthy;
    std::optional<std::string> errorMessage;

    void addErrorMessageToJsonIfPresent(Json::Value& json);
    Json::Value toJson();
};

namespace drogon
{
template<>
inline HttpResponsePtr toResponse(HealthcheckResponse&& response)
{ return HttpResponse::newHttpJsonResponse(response.toJson()); }
}