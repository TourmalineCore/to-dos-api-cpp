#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <cstdlib>
#include <string>

class AppConfig
{
public:
    /**
     * @brief Function for retrieving the value of an environment variable
     * @param name is the name of the environment variable
     * @param defaultValue is the value that will be used if the environment variable doesn't exist
     * @return std::string
     */
    static std::string getEnv(std::string name, std::string defaultValue)
    {
        char* value = std::getenv(name.c_str());
        return value ? std::string(value) : defaultValue;
    }

    /**
     * @brief Function to get the host value from the environment
     * variable `API_HOST`. Default is `0.0.0.0`
     * @return std::string
     */
    static std::string apiHost() { return getEnv("API_HOST", "0.0.0.0"); }

    /**
     * @brief Function to get the port value from the environment
     * variable `API_PORT`. Default is `80`
     * @return int
     */
    static int apiPort() { return std::stoi(getEnv("API_PORT", "80")); }

    /**
     * @brief Function to get the log level value from the environment
     * variable `API_LOG_LEVEL`. Default is `INFO`
     * @note Possible values: INFO, WARN, TRACE, DEBUG
     * @return std::string
     */
    static std::string apiLogLevel() { return getEnv("API_LOG_LEVEL", "INFO"); }

    /**
     * @brief Function to get the numbers of threads value from the
     * environment variable `API_NUMBER_OF_THREADS`. Default is `1`
     * @return int
     */
    static int apiNumThreads() { return std::stoi(getEnv("API_NUMBER_OF_THREADS", "1")); }

    /**
     * @brief Function to get the database host value from the
     * environment variable `POSTGRES_HOST`. Default is `0.0.0.0`
     * @return std::string
     */
    static std::string databaseHost() { return getEnv("POSTGRES_HOST", "0.0.0.0"); }

    /**
     * @brief Function to get the database port value from the
     * environment variable `POSTGRES_PORT`. Default is `5432`
     * @return std::string
     */
    static std::string databasePort() { return getEnv("POSTGRES_PORT", "5432"); }

    /**
     * @brief Function to get the database name value from the
     * environment variable `POSTGRES_DB`. Default is
     * `to-dos-api-cpp-db`
     * @return std::string
     */
    static std::string databaseName() { return getEnv("POSTGRES_DB", "to-dos-api-cpp-db"); }

    /**
     * @brief Function to get the database user value from the
     * environment variable `POSTGRES_USER`. Default is `postgres`
     * @return std::string
     */
    static std::string databaseUser() { return getEnv("POSTGRES_USER", "postgres"); }

    /**
     * @brief Function to get the database password value from the
     * environment variable `POSTGRES_PASSWORD`. Default is
     * `password`
     * @return std::string
     */
    static std::string databasePassword() { return getEnv("POSTGRES_PASSWORD", "password"); }
};

#endif  // APP_CONFIG_H