#include "db_connection.h"
#include "app-config.h"

#include <cstdlib>
#include <stdexcept>

#include <odb/pgsql/database.hxx>

std::shared_ptr<odb::database> DbConnection::instance_ = nullptr;

std::shared_ptr<odb::database> DbConnection::get()
{
    static std::once_flag flag;
    std::call_once(
        flag,
        []()
        {
            const std::string host = AppConfig::databaseHost();
            const std::string port = AppConfig::databasePort();
            const std::string user = AppConfig::databaseUser();
            const std::string password = AppConfig::databasePassword();
            const std::string dbname = AppConfig::databaseName();

            std::string conn = "host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + password;

            instance_ = std::shared_ptr<odb::database>(new odb::pgsql::database(conn));
        }
    );

    return instance_;
}