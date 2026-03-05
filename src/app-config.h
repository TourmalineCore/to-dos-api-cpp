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
     * variable `ApiOptions__Host`. Default is `0.0.0.0`
     * @return std::string
     */
    static std::string apiOptionHost() { return getEnv("ApiOptions__Host", "0.0.0.0"); }

    /**
     * @brief Function to get the port value from the environment
     * variable `ApiOptions__Port`. Default is `80`
     * @return int
     */
    static int apiOptionPort() { return std::stoi(getEnv("ApiOptions__Port", "80")); }

    /**
     * @brief Function to get the log level value from the environment
     * variable `ApiOptions__LogLevel`. Default is `INFO`
     * @note Possible values: INFO, WARN, TRACE, DEBUG
     * @return std::string
     */
    static std::string apiOptionLogLevel() { return getEnv("ApiOptions__LogLevel", "INFO"); }

    /**
     * @brief Function to get the numbers of threads value from the
     * environment variable `ApiOptions__NumberOfThreads`. Default is `1`
     * @return int
     */
    static int apiOptionNumThreads() { return std::stoi(getEnv("ApiOptions__NumberOfThreads", "1")); }

    /**
     * @brief Function to get the database host value from the
     * environment variable `DatabaseCredentials__Host`. Default is `0.0.0.0`
     * @return std::string
     */
    static std::string databaseHost() { return getEnv("DatabaseCredentials__Host", "0.0.0.0"); }

    /**
     * @brief Function to get the database port value from the
     * environment variable `DatabaseCredentials__Port`. Default is `5432`
     * @return std::string
     */
    static std::string databasePort() { return getEnv("DatabaseCredentials__Port", "5432"); }

    /**
     * @brief Function to get the database name value from the
     * environment variable `DatabaseCredentials__Name`. Default is
     * `to-dos-api-cpp-db`
     * @return std::string
     */
    static std::string databaseName() { return getEnv("DatabaseCredentials__Name", "to-dos-api-cpp-db"); }

    /**
     * @brief Function to get the database user value from the
     * environment variable `DatabaseCredentials__User`. Default is `postgres`
     * @return std::string
     */
    static std::string databaseUser() { return getEnv("DatabaseCredentials__User", "postgres"); }

    /**
     * @brief Function to get the database password value from the
     * environment variable `DatabaseCredentials__Password`. Default is
     * `password`
     * @return std::string
     */
    static std::string databasePassword() { return getEnv("DatabaseCredentials__Password", "password"); }
};

#endif  // APP_CONFIG_H