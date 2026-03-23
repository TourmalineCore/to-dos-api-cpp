#include "utils/app-config/app-config.h"
#include <drogon/HttpAppFramework.h>

int main()
{
    // We need to set the logging level so that it is used instead of the default
    drogon::app().setLogLevel(AppConfig::apiLogLevel());

    auto& config = AppConfig::GetInstance();

    drogon::app().addListener(config.apiHost(), config.apiPort()).setThreadNum(config.apiNumThreads());
    drogon::app().run();

    return 0;
}
