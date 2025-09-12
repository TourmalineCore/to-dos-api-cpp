#pragma once

#include "data/models/to-do.h"
#include <memory>
#include <odb/database.hxx>
#include <vector>

class ToDoQueries
{
public:
    ToDoQueries
(odb::database& db) : db_(db) {}
    std::shared_ptr<std::vector<ToDo>> get_all_todos();
    std::shared_ptr<ToDo> get_todo_by_id(int id);

private:
    odb::database& db_;
};