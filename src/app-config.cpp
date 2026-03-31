#include "app-config.h"

AppConfig::AppConfig()
{
    setApiHost(getEnv("API_HOST", "0.0.0.0"));
    setApiPort(getEnvInt("API_PORT", 80));
    setApiNumThreads(getEnvInt("API_NUMBER_OF_THREADS", 1));
    setDatabaseHost(getEnv("POSTGRES_HOST", "0.0.0.0"));
    setDatabasePort(getEnv("POSTGRES_PORT", "5432"));
    setDatabaseName(getEnv("POSTGRES_DB", "to-dos-api-cpp-db"));
    setDatabaseUser(getEnv("POSTGRES_USER", "postgres"));
    setDatabasePassword(getEnv("POSTGRES_PASSWORD", "password"));
}

AppConfig& AppConfig::GetInstance()
{
        static AppConfig instance;
    return instance;
}

std::string AppConfig::getEnv(std::string name, std::string defaultValue)
{
    char* value = std::getenv(name.c_str());

    if (value)
    {
        return std::string(value);
    }
    else
    {
        LOG_WARN << "Failed to get the value of the " << name << " environment variable; the default value will be used: " << defaultValue;
        return defaultValue;
    }
}

uint32_t AppConfig::getEnvInt(std::string name, uint32_t defaultValue)
{
    char* value = std::getenv(name.c_str());

    if (!value)
        return defaultValue;

    try
    {
        auto result = std::stoi(value);
        auto limit = std::numeric_limits<uint32_t>::max();

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

void AppConfig::setApiHost(std::string apiHost)
{
    apiHost_ = apiHost;
    LOG_DEBUG << "Update value: apiHost_=" << apiHost_;
};

void AppConfig::setApiPort(uint32_t apiPort)
{
    apiPort_ = apiPort;
    LOG_DEBUG << "Update value: apiPort_=" << apiPort_;
};

void AppConfig::setApiNumThreads(uint32_t apiNumThreads)
{
    uint32_t numberOfThreads = apiNumThreads;

    if (numberOfThreads > 0)
    {
        apiNumThreads_ = numberOfThreads;
    }
    else
    {
        apiNumThreads_ = 1;
        LOG_ERROR << "The number of allocated threads cannot be less than 1";
    }

    LOG_DEBUG << "Update value: apiNumThreads_=" << apiNumThreads_;
};

void AppConfig::setDatabaseHost(std::string databaseHost)
{
    databaseHost_ = databaseHost;
    LOG_DEBUG << "Update value: databaseHost_=" << databaseHost_;
};

void AppConfig::setDatabasePort(std::string databasePort)
{
    databasePort_ = databasePort;
    LOG_DEBUG << "Update value: databasePort_=" << databasePort_;
};

void AppConfig::setDatabaseName(std::string databaseName)
{
    databaseName_ = databaseName;
    LOG_DEBUG << "Update value: databaseName_=" << databaseName_;
};

void AppConfig::setDatabaseUser(std::string databaseUser)
{
    databaseUser_ = databaseUser;
    LOG_DEBUG << "Update value: databaseUser_=" << databaseUser_;
};

void AppConfig::setDatabasePassword(std::string databasePassword)
{
    databasePassword_ = databasePassword;
    LOG_DEBUG << "Update value: databasePassword_=" << databasePassword_;
};

const std::string& AppConfig::getApiHost() const
{ return apiHost_; }

const uint32_t& AppConfig::getApiPort() const
{ return apiPort_; }

const uint32_t& AppConfig::getApiNumThreads() const
{ return apiNumThreads_; }

const trantor::Logger::LogLevel AppConfig::getApiLogLevel()
{ return parseLogLevel(getEnv("API_LOG_LEVEL", "INFO")); }

const std::string& AppConfig::getDatabaseHost() const
{ return databaseHost_; }

const std::string& AppConfig::getDatabasePort() const
{ return databasePort_; }

const std::string& AppConfig::getDatabaseName() const
{ return databaseName_; }

const std::string& AppConfig::getDatabaseUser() const
{ return databaseUser_; }

const std::string& AppConfig::getDatabasePassword() const
{ return databasePassword_; }