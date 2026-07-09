#pragma once

#include "healthcheck-response.h"

class HealthcheckHandler
{
public:
    explicit HealthcheckHandler() {};

    HealthcheckResponse handle();
};