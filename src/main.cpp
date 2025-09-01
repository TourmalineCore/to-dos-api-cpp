#include "to-dos-api.h"
#include <vector>
#include <string>
// #include <orm/db.hpp>
// #include <orm/utils/configuration.hpp>

#include <drogon/HttpAppFramework.h>
// #include "controllers/simple-controller.h"

// using Orm::DB;

// using ConfigUtils = Orm::Utils::Configuration;

// using namespace Orm::Constants;

int main() {
    // auto manager = DB::create({
    // {"driver",             "QPSQL"},
    // {"host",               qEnvironmentVariable("DB_HOST", "127.0.0.1")},
    // {"port",               qEnvironmentVariable("DB_PORT", "5432")},
    // {"database",           qEnvironmentVariable("DB_DATABASE", "postgres")},
    // {"search_path",        qEnvironmentVariable("DB_SEARCHPATH", "public")},
    // {"username",           qEnvironmentVariable("DB_USERNAME", "postgres")},
    // {"password",           qEnvironmentVariable("DB_PASSWORD", "postgres")},
    // {"charset",            qEnvironmentVariable("DB_CHARSET", "utf8")},
    // {"timezone",           "UTC"},
    // /* Specifies what time zone all QDateTime-s will have, the overridden default is
    //    the QTimeZone::UTC, set to the QTimeZone::LocalTime or
    //    QtTimeZoneType::DontConvert to use the system local time. */
    // // {"qt_timezone",        QVariant::fromValue(QTimeZone::UTC)},
    // {"prefix",             ""},
    // {"prefix_indexes",     false},
    // {"options",            QVariantHash()},
    // });

    drogon::app().setLogLevel(trantor::Logger::kDebug);
    // drogon::app().addListener("127.0.0.1",8080);
    // drogon::app().setThreadNum(std::thread::hardware_concurrency());
    
    drogon::app().loadConfigFile("/workspaces/to-dos-api-cpp/config.json");
    drogon::app().run();
    return 0;
}
