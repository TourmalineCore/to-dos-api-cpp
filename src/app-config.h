#pragma once

#include <cstdlib>
#include <stdexcept>
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
    std::uint32_t apiPort_;
    std::uint32_t apiNumThreads_;

    std::string databaseHost_;
    std::string databasePort_;
    std::string databaseName_;
    std::string databaseUser_;
    std::string databasePassword_;

    /**
     * @brief Setter for the `apiHost_` variable
     * @param apiHost is host on which the API will be run
     * @return void
     */
    void setApiHost(std::string apiHost);

    /**
     * @brief Setter for the `apiPort_` variable
     * @param apiPort is port on which the API will be run
     * @return void
     */
    void setApiPort(std::uint32_t apiPort);

    /**
     * @brief Setter for the `apiNumThreads_` variable
     * @param apiNumThreads is number of threads on which the API will run
     * @return void
     */
    void setApiNumThreads(std::uint32_t apiNumThreads);

    /**
     * @brief Setter for the `databaseHost_` variable
     * @param databaseHost is the host that the API will use to connect to the database
     * @return void
     */
    void setDatabaseHost(std::string databaseHost);

    /**
     * @brief Setter for the `databasePort_` variable
     * @param databasePort is the port that the API will use to connect to the database
     * @return void
     */
    void setDatabasePort(std::string databasePort);

    /**
     * @brief Setter for the `databaseName_` variable
     * @param databaseName is the name that the API will use to connect to the database
     * @return void
     */
    void setDatabaseName(std::string databaseName);

    /**
     * @brief Setter for the `databaseUser_` variable
     * @param databaseUser is the user that the API will use to connect to the database
     * @return void
     */
    void setDatabaseUser(std::string databaseUser);

    /**
     * @brief Setter for the `databasePassword_` variable
     * @param databasePassword is the password that the API will use to connect to the database
     * @return void
     */
    void setDatabasePassword(std::string databasePassword);

public:
    /**
     * @brief Function to retrieve an instance of the AppConfig class
     * @return an instance of the AppConfig class
     */
    static AppConfig& GetInstance();

    /**
     * @brief Function for retrieving the value of an environment variable
     * @param name is the name of the environment variable
     * @return std::string
     */
    static std::string getEnv(std::string name);

    /**
     * @brief Function that retrieves a value from an environment variable and converts it to an integer type
     * @param name is the name of the environment variable
     * @return std::uint32_t
     */
    static std::uint32_t getEnvInt(std::string name);

    /**
     * @brief Function for converting a string representing a logging level to the `trantor` type. Default is `trantor::Logger::kError`
     * @param level is a string containing the logging level.
     */
    static trantor::Logger::LogLevel parseLogLevel(const std::string& level);

    /**
     * @brief Getter for the `apiHost_` variable
     * @return const std::string
     */
    const std::string& getApiHost() const;

    /**
     * @brief Getter for the `apiPort_` variable
     * @return const std::uint32_t
     */
    const std::uint32_t& getApiPort() const;

    /**
     * @brief Getter for the `apiNumThreads_` variable
     * @return const std::uint32_t
     */
    const std::uint32_t& getApiNumThreads() const;

    /**
     * @brief Getter for the `apiLogLevel_` variable
     * @note The method must be static so that the level can be set before the class is initialized;
     * otherwise, logs from other levels will be displayed
     * @return const trantor::Logger::LogLevel
     */
    static const trantor::Logger::LogLevel getApiLogLevel();

    /**
     * @brief Getter for the `databaseHost_` variable
     * @return const std::string
     */
    const std::string& getDatabaseHost() const;

    /**
     * @brief Getter for the `databasePort_` variable
     * @return const std::string
     */
    const std::string& getDatabasePort() const;

    /**
     * @brief Getter for the `databaseName_` variable
     * @return const std::string
     */
    const std::string& getDatabaseName() const;

    /**
     * @brief Getter for the `databaseUser_` variable
     * @return const std::string
     */
    const std::string& getDatabaseUser() const;

    /**
     * @brief Getter for the `databasePassword_` variable
     * @return const std::string
     */
    const std::string& getDatabasePassword() const;
};