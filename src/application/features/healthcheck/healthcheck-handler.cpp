#include "healthcheck-handler.h"

HealthcheckResponse HealthcheckHandler::handle()
{
    // This is where the logic for checking the database
    // connection and similar operations can be located.
    // ...

    HealthcheckResponse response = { .isHealthy = true };

    return response;
};