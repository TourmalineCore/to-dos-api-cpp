#pragma once

#include <memory>
#include <odb/database.hxx>

class DbConnection
{
public:
    static std::shared_ptr<odb::database> get();

private:
    DbConnection() = default;
    static std::shared_ptr<odb::database> instance_;
};