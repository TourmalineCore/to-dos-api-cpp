#include "db_connection.h"

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
            const std::string user = std::getenv("POSTGRES_USER");
            const std::string password = std::getenv("POSTGRES_PASSWORD");
            const std::string db_name = std::getenv("POSTGRES_DB");
            const std::string host = std::getenv("POSTGRES_HOST");
            const std::string port = std::getenv("POSTGRES_PORT");

            std::string conninfo = "host=" + host + " port=" + port + " dbname=" + db_name + " user=" + user + " password=" + password;

            instance_ = std::shared_ptr<odb::database>(new odb::pgsql::database(conninfo));
        }
    );

    return instance_;
}