#include "app-config.h"

AppConfig::AppConfig()
{
    setApiHost(getEnv("API_HOST"));
    setApiPort(getEnvInt("API_PORT"));
    setApiNumThreads(getEnvInt("API_NUMBER_OF_THREADS"));
    setDatabaseHost(getEnv("POSTGRES_HOST"));
    setDatabasePort(getEnv("POSTGRES_PORT"));
    setDatabaseName(getEnv("POSTGRES_DB"));
    setDatabaseUser(getEnv("POSTGRES_USER"));
    setDatabasePassword(getEnv("POSTGRES_PASSWORD"));
}

AppConfig& AppConfig::GetInstance()
{
    static AppConfig instance;
    return instance;
}

std::string AppConfig::getEnv(std::string name)
{
    char* value = std::getenv(name.c_str());

    if (!value) {
        throw std::invalid_argument(
            "error: failed to extract the " + name + " environment variable value"
        );
    }

    return std::string(value);
}

std::uint32_t AppConfig::getEnvInt(std::string name)
{
    char* value = std::getenv(name.c_str());

    if (!value) {
        throw std::invalid_argument(
            "error: failed to extract the " + name + " environment variable value"
        );
    }

    auto result = std::stoi(value);
    auto limit = std::numeric_limits<std::uint32_t>::max();

    if (result < 0 || result > limit)
        throw std::overflow_error(
            "error: an attempt to write a " + name + " value which is larger than what can be stored in a " + std::to_string(limit)
        );

    return static_cast<std::uint32_t>(result);
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

void AppConfig::setApiPort(std::uint32_t apiPort)
{
    apiPort_ = apiPort;
    LOG_DEBUG << "Update value: apiPort_=" << apiPort_;
};

void AppConfig::setApiNumThreads(std::uint32_t apiNumThreads)
{
    std::uint32_t numberOfThreads = apiNumThreads;

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

const std::uint32_t& AppConfig::getApiPort() const
{ return apiPort_; }

const std::uint32_t& AppConfig::getApiNumThreads() const
{ return apiNumThreads_; }

const trantor::Logger::LogLevel AppConfig::getApiLogLevel()
{ return parseLogLevel(getEnv("API_LOG_LEVEL")); }

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