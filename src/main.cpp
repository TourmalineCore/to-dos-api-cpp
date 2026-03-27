#include "utils/app-config/app-config.h"
#include <drogon/HttpAppFramework.h>

int main()
{
    // We need to set the logging level right away; otherwise, the default level
    // will be used until .setLogLevel is called
    drogon::app().setLogLevel(AppConfig::getApiLogLevel());

    auto& config = AppConfig::GetInstance();

    drogon::app().addListener(config.getApiHost(), config.getApiPort()).setThreadNum(config.getApiNumThreads());
    drogon::app().run();

    return 0;
}
