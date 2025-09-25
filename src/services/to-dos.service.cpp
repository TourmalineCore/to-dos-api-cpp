#include "to-dos.service.h"
#include <chrono>
#include <ctime>

using std::string;
using std::vector;

static vector<ToDoDTO> mapToDTOs(const std::shared_ptr<std::vector<ToDo>>& todos)
{
    vector<ToDoDTO> out;
    out.reserve(todos ? todos->size() : 0);
    if (todos)
    {
        for (const auto& t : *todos)
        {
            ToDoDTO dto;
            dto.id = static_cast<int>(t.id());
            dto.name = t.name();
            out.push_back(std::move(dto));
        }
    }
    return out;
}

void ToDoService::addToDo(const string name)
{
    const std::time_t now_utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    (void) _commands.create_todo(name, now_utc);
}

// TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/38): add here a check for not found todos
bool ToDoService::completeToDo(int id)
{
    (void) _commands.soft_delete_todo(id);
    return true;
}

// TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/38): add here a check for not found todos
bool ToDoService::deleteToDo(int id)
{
    (void) _commands.delete_todo(id);
    return true;
}

const Json::Value ToDoService::getToDos() const
{
    Json::Value json;
    Json::Value toDosArray(Json::arrayValue);

    auto todos = _queries.get_all_todos();
    auto dtos = mapToDTOs(todos);
    for (const auto& dto : dtos)
    {
        toDosArray.append(dto.toJson());
    }
    json["toDos"] = toDosArray;
    return json;
}