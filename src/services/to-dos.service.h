#pragma once

#include "data/commands/todo-commands.h"
#include "data/queries/todo-queries.h"
#include "dtos/to-dos-dto.h"

#include <json/json.h>
#include <string>
#include <vector>

class ToDoService
{
private:
    ToDoQueries& _queries;
    ToDoCommands& _commands;

public:
    explicit ToDoService(ToDoQueries& queries, ToDoCommands& commands)
    : _queries(queries),
      _commands(commands)
    {}

    void addToDo(const std::string description);
    bool completeToDo(int id);
    bool deleteToDo(int id);
    const Json::Value getToDos() const;
};