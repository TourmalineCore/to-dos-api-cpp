#include "to-dos-api.h"
#include <vector>
#include <string>

#include <drogon/HttpAppFramework.h>
#include "controllers/simple-controller.h"

int main() {
    drogon::app().setLogLevel(trantor::Logger::kDebug);
    drogon::app().addListener("127.0.0.1",8080);

    drogon::app().run();
    return 0;
}
