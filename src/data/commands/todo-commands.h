#pragma once

#include "data/models/to-do.h"
#include <memory>
#include <odb/database.hxx>

class ToDoCommands
{
public:
    ToDoCommands
(odb::database& db) : db_(db) {}

    uint64_t create_todo(const std::string& name, std::time_t createdAtUtc);
    uint64_t delete_todo(int id);
    uint64_t soft_delete_todo(int id);

private:
    odb::database& db_;
};