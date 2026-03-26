#pragma once

#include "to-do.h"
#include <memory>
#include <odb/database.hxx>
#include <vector>

class GetToDoById
{
public:
    GetToDoById(odb::database& db)
    : db_(db)
    {}
    std::shared_ptr<ToDo> get(int id);

private:
    odb::database& db_;
};