#include <trantor/utils/Logger.h>

#include "app-config.h"

std::string AppConfig::getEnv(std::string name, std::string defaultValue)
{
    char* value = std::getenv(name.c_str());
    return value ? std::string(value) : defaultValue;
}

std::string AppConfig::apiHost()
{
    return getEnv("API_HOST", "0.0.0.0");
}

int AppConfig::apiPort()
{
    return std::stoi(getEnv("API_PORT", "80"));
}

trantor::Logger::LogLevel AppConfig::apiLogLevel()
{
    auto logLevel = getEnv("API_LOG_LEVEL", "INFO");

    trantor::Logger::LogLevel level;

    if (logLevel == "DEBUG")
        level = trantor::Logger::kDebug;
    else if (logLevel == "WARN")
        level = trantor::Logger::kWarn;
    else if (logLevel == "TRACE")
        level = trantor::Logger::kTrace;
    else
        level = trantor::Logger::kInfo;

    return level;
}

int AppConfig::apiNumThreads()
{
    return std::stoi(getEnv("API_NUMBER_OF_THREADS", "1"));
}

std::string AppConfig::databaseHost()
{
    return getEnv("POSTGRES_HOST", "0.0.0.0");
}

std::string AppConfig::databasePort()
{
    return getEnv("POSTGRES_PORT", "5432");
}

std::string AppConfig::databaseName()
{
    return getEnv("POSTGRES_DB", "to-dos-api-cpp-db");
}

std::string AppConfig::databaseUser()
{
    return getEnv("POSTGRES_USER", "postgres");
}

std::string AppConfig::databasePassword()
{
    return getEnv("POSTGRES_PASSWORD", "password");
}