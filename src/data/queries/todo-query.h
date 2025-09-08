#pragma once

#include "data/models/to-do.h"
#include <memory>
#include <odb/database.hxx>

class ToDoQuery
{
public:
    ToDoQuery(odb::database& db) : db_(db) {}

    void add_todo(const std::string& name, std::time_t createdAtUtc);
    std::shared_ptr<ToDo> get_todo_by_id(int id);

private:
    odb::database& db_;
};