#include "app-config.h"

AppConfig::AppConfig()
{
    apiHost();
    apiPort();
    apiNumThreads();
    databaseHost();
    databasePort();
    databaseName();
    databaseUser();
    databasePort();
}

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

uint32_t AppConfig::getEnvInt(std::string name, uint32_t defaultValue)
{
    char* value = std::getenv(name.c_str());

    if (!value)
        return defaultValue;

    try
    {
        auto result = std::stoi(value);
        auto limit = std::numeric_limits<uint8_t>::max();

        if (result < 0 || result > limit)
            throw std::overflow_error(
                "error: an attempt to write a " + name + " value which is larger than what can be stored in a " + std::to_string(limit)
            );

        return static_cast<uint32_t>(result);
    }
    catch (const std::exception& e)
    {
        LOG_ERROR << e.what();
        return defaultValue;
    }
}

trantor::Logger::LogLevel AppConfig::parseLogLevel(const std::string& level)
{
    // kTrace < kDebug < kInfo < kWarn < kError
    if (level == "TRACE")
        return trantor::Logger::kTrace;
    else if (level == "DEBUG")
        return trantor::Logger::kDebug;
    else if (level == "INFO")
        return trantor::Logger::kInfo;
    else if (level == "WARN")
        return trantor::Logger::kWarn;
    else
        return trantor::Logger::kError;
}

const std::string& AppConfig::apiHost()
{
    if (apiHost_.empty())
    {
        apiHost_ = getEnv("API_HOST", "0.0.0.0");
        LOG_DEBUG << "Update value: apiHost_=" << apiHost_;
    }

    return apiHost_;
}

const uint32_t& AppConfig::apiPort()
{
    if (!apiPort_)
    {
        apiPort_ = getEnvInt("API_PORT", 80);
        LOG_DEBUG << "Update value: apiPort_=" << apiPort_;
    }

    return apiPort_;
}

const uint32_t& AppConfig::apiNumThreads()
{
    if (!apiNumThreads_)
    {
        uint32_t numberOfThreads = getEnvInt("API_NUMBER_OF_THREADS", 1);
        apiNumThreads_ = numberOfThreads > 0 ? numberOfThreads : 1;
        LOG_ERROR << "The number of allocated threads cannot be less than 1";
        LOG_DEBUG << "Update value: apiNumThreads_=" << apiNumThreads_;
    }

    return apiNumThreads_;
}

const trantor::Logger::LogLevel AppConfig::apiLogLevel()
{
    return parseLogLevel(getEnv("API_LOG_LEVEL", "INFO"));
}

const std::string& AppConfig::databaseHost()
{
    if (databaseHost_.empty())
    {
        databaseHost_ = getEnv("POSTGRES_HOST", "0.0.0.0");
        LOG_DEBUG << "Update value: databaseHost_=" << databaseHost_;
    }

    return databaseHost_;
}

const std::string& AppConfig::databasePort()
{
    if (databasePort_.empty())
    {
        databasePort_ = getEnv("POSTGRES_PORT", "5432");
        LOG_DEBUG << "Update value: databasePort_=" << databasePort_;
    }

    return databasePort_;
}

const std::string& AppConfig::databaseName()
{
    if (databaseName_.empty())
    {
        databaseName_ = getEnv("POSTGRES_DB", "to-dos-api-cpp-db");
        LOG_DEBUG << "Update value: databaseName_=" << databaseName_;
    }

    return databaseName_;
}

const std::string& AppConfig::databaseUser()
{
    if (databaseUser_.empty())
    {
        databaseUser_ = getEnv("POSTGRES_USER", "postgres");
        LOG_DEBUG << "Update value: databaseUser_=" << databaseUser_;
    }

    return databaseUser_;
}

const std::string& AppConfig::databasePassword()
{
    if (databasePassword_.empty())
    {
        databasePassword_ = getEnv("POSTGRES_PASSWORD", "password");
        LOG_DEBUG << "Update value: databasePassword_=" << databasePassword_;
    }

    return databasePassword_;
}