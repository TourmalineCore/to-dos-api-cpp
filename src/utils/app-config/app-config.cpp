#include "app-config.h"

AppConfig::AppConfig()
: apiHost_(getEnv("API_HOST", "0.0.0.0")),
  apiPort_(getEnvInt("API_PORT", 80)),
  apiNumThreads_(getEnvInt("API_NUMBER_OF_THREADS", 1)),
  apiLogLevel_(parseLogLevel(getEnv("API_LOG_LEVEL", "INFO"))),
  databaseHost_(getEnv("POSTGRES_HOST", "0.0.0.0")),
  databasePort_(getEnv("POSTGRES_PORT", "5432")),
  databaseName_(getEnv("POSTGRES_DB", "to-dos-api-cpp-db")),
  databaseUser_(getEnv("POSTGRES_USER", "postgres")),
  databasePassword_(getEnv("POSTGRES_PASSWORD", "password"))
{}

AppConfig& AppConfig::GetInstance()
{
    static AppConfig instance;
    return instance;
}

std::string AppConfig::getEnv(std::string name, std::string defaultValue)
{
    char* value = std::getenv(name.c_str());
    return value ? std::string(value) : defaultValue;
}

int AppConfig::getEnvInt(std::string name, int defaultValue)
{
    char* value = std::getenv(name.c_str());

    if (!value)
        return defaultValue;

    try
    {
        return std::stoi(value);
    }
    catch (const std::exception&)
    {
        return defaultValue;
    }
}

trantor::Logger::LogLevel AppConfig::parseLogLevel(const std::string& level)
{
    if (level == "DEBUG")
        return trantor::Logger::kDebug;
    if (level == "WARN")
        return trantor::Logger::kWarn;
    if (level == "TRACE")
        return trantor::Logger::kTrace;
    return trantor::Logger::kInfo;
}