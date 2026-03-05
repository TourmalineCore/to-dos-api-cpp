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
            std::string dbConnectionString = AppConfig::databaseDefaultConnectionString();

            instance_ = std::shared_ptr<odb::database>(new odb::pgsql::database(dbConnectionString));
        }
    );

    return instance_;
}