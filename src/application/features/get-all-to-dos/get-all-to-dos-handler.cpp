#include "get-all-to-dos-handler.h"

using std::vector;

static vector<ToDoDTO> mapToDTOs(const std::shared_ptr<vector<ToDo>>& todos)
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

GetAllToDosResponse GetAllToDosHandler::handle()
{
    auto todos = _getAllToDosQuery.get();
    return { mapToDTOs(todos) };
}