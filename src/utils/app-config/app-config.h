#pragma once

#include <cstdlib>
#include <drogon/drogon.h>
#include <limits>
#include <string>
#include <trantor/utils/Logger.h>

class AppConfig
{
private:
    /**
     * @brief AppConfig class constructor
     * @return void
     */
    AppConfig();

    // No copying
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    std::string apiHost_;
    uint32_t apiPort_ = 0;
    uint32_t apiNumThreads_ = 0;

    std::string databaseHost_;
    std::string databasePort_;
    std::string databaseName_;
    std::string databaseUser_;
    std::string databasePassword_;

public:
    /**
     * @brief Function to retrieve an instance of the AppConfig class
     * @return an instance of the AppConfig class
     */
    static AppConfig& GetInstance();

    /**
     * @brief Function for retrieving the value of an environment variable
     * @param name is the name of the environment variable
     * @param defaultValue is the value that will be used if the environment variable doesn't exist
     * @return std::string
     */
    static std::string getEnv(std::string name, std::string defaultValue);

    /**
     * @brief Function that retrieves a value from an environment variable and converts it to an integer type
     * @param name is the name of the environment variable
     * @param defaultValue is the value that will be used if the environment variable doesn't exist
     * @return uint32_t
     */
    static uint32_t getEnvInt(std::string name, uint32_t defaultValue);

    /**
     * @brief Function for converting a string representing a logging level to the `trantor` type. Default is `trantor::Logger::kError`
     * @param level is a string containing the logging level.
     */
    static trantor::Logger::LogLevel parseLogLevel(const std::string& level);

    /**
     * @brief Getter for the host value from the environment
     * variable `API_HOST`. Default is `0.0.0.0`
     * @return const std::string
     */
    const std::string& apiHost();

    /**
     * @brief Getter for the port value from the environment
     * variable `API_PORT`. Default is `80`
     * @return const uint32_t
     */
    const uint32_t& apiPort();

    /**
     * @brief Getter for the numbers of threads value from the
     * environment variable `API_NUMBER_OF_THREADS`. Default is `1`
     * @return const uint32_t
     */
    const uint32_t& apiNumThreads();

    /**
     * @brief Function for getting the log level value from the environment
     * variable `API_LOG_LEVEL`. Default is `INFO`
     * @note The method must be static so that the level can be set before the class is initialized;
     * otherwise, logs from other levels will be displayed.
     * @return const trantor::Logger::LogLevel
     */
    static const trantor::Logger::LogLevel apiLogLevel();

    /**
     * @brief Getter for the database host value from the
     * environment variable `POSTGRES_HOST`. Default is `0.0.0.0`
     * @return const std::string
     */
    const std::string& databaseHost();

    /**
     * @brief Getter for the database port value from the
     * environment variable `POSTGRES_PORT`. Default is `5432`

     * @return const std::string
     */
    const std::string& databasePort();

    /**
     * @brief Getter for the database name value from the
     * environment variable `POSTGRES_DB`. Default is
     * `to-dos-api-cpp-db`
     * @return const std::string
     */
    const std::string& databaseName();

    /**
     * @brief Getter for the database user value from the
     * environment variable `POSTGRES_USER`. Default is `postgres`
     * @return const std::string
     */
    const std::string& databaseUser();

    /**
     * @brief Getter for the database password value from the
     * environment variable `POSTGRES_PASSWORD`. Default is
     * `password`
     * @return const std::string
     */
    const std::string& databasePassword();
};