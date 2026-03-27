#include "get-to-do-by-id-handler.h"

static ToDoDTO mapToDTO(const ToDo& todo)
{
    ToDoDTO dto;
    dto.id = static_cast<int>(todo.id());
    dto.name = todo.name();
    return dto;
}

GetToDoByIdResponse GetToDoByIdHandler::handle(uint64_t id)
{
    auto todo = _getToDoByIdQuery.get(static_cast<int>(id));

    if (!todo)
        return { std::nullopt };

    return { mapToDTO(*todo) };
}