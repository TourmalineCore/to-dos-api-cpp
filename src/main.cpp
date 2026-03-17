#include "app-config.h"
#include <cstdlib>
#include <drogon/HttpAppFramework.h>
#include <trantor/utils/Logger.h>

int main()
{
    drogon::app()
        .addListener(AppConfig::apiHost(), AppConfig::apiPort())
        .setLogLevel(AppConfig::apiLogLevel())
        .setThreadNum(AppConfig::apiNumThreads());

    drogon::app().run();

    return 0;
}
