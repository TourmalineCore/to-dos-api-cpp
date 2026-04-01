#pragma once

#include "to-do.h"
#include <memory>
#include <odb/database.hxx>
#include <vector>

class GetAllToDosQuery
{
public:
    GetAllToDosQuery(odb::database& db)
    : db_(db)
    {}
    std::shared_ptr<std::vector<ToDo>> get();

private:
    odb::database& db_;
};