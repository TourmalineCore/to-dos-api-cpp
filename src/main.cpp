#include "utils/app-config/app-config.h"
#include <drogon/HttpAppFramework.h>

int main()
{
    auto& config = AppConfig::GetInstance();

    drogon::app().addListener(config.apiHost(), config.apiPort()).setLogLevel(config.apiLogLevel()).setThreadNum(config.apiNumThreads());

    drogon::app().run();

    return 0;
}
