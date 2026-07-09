#include "healthcheck-response.h"

void HealthcheckResponse::addErrorMessageToJsonIfPresent(Json::Value& json)
{
    if (errorMessage.has_value())
    {
        json["errorMessage"] = *errorMessage;
    }
}

Json::Value HealthcheckResponse::toJson()
{
    Json::Value json;

    if (isHealthy == true)
    {
        json["status"] = "ok";
    }
    else
    {
        json["status"] = "error";
        addErrorMessageToJsonIfPresent(json);
    }

    return json;
}