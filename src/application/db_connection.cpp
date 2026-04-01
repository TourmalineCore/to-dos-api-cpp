#include "db_connection.h"
#include "../app-config.h"

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
            auto& config = AppConfig::GetInstance();

            const std::string host = config.getDatabaseHost();
            const std::string port = config.getDatabasePort();
            const std::string user = config.getDatabaseUser();
            const std::string password = config.getDatabasePassword();
            const std::string dbname = config.getDatabaseName();

            std::string conn = "host=" + host + " port=" + port + " dbname=" + dbname + " user=" + user + " password=" + password;

            instance_ = std::shared_ptr<odb::database>(new odb::pgsql::database(conn));
        }
    );

    return instance_;
}