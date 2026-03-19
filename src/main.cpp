#include "controllers/app-controller.h"
#include <cstdlib>
#include <drogon/HttpAppFramework.h>

int main()
{
    drogon::app().addListener("127.0.0.1", 8080).setLogLevel(trantor::Logger::kInfo).setThreadNum(1);

    drogon::app().run();

    return 0;
}
