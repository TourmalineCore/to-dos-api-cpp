#include "app-config.h"
#include <cstdlib>
#include <drogon/HttpAppFramework.h>
#include <trantor/utils/Logger.h>

int main()
{
    trantor::Logger::LogLevel level = trantor::Logger::kDebug;
    auto logLevel = AppConfig::drogonLogLevel();
    if (logLevel == "INFO")
        level = trantor::Logger::kInfo;
    else if (logLevel == "WARN")
        level = trantor::Logger::kWarn;
    else if (logLevel == "TRACE")
        level = trantor::Logger::kTrace;

    // This is necessary to display API calls to endpoints in the logs
    drogon::app().registerPreHandlingAdvice(
        [](const drogon::HttpRequestPtr& req)
        {
            LOG_INFO << req->getMethodString() << " "
                     << req->getPath();
        }
    );

    drogon::app()
        .addListener(AppConfig::drogonHost(), AppConfig::drogonPort())
        .setLogLevel(level)
        .setThreadNum(AppConfig::drogonNumThreads());

    drogon::app().run();

    return 0;
}
