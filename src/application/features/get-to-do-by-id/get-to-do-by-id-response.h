#pragma once
#include "../../shared-dtos/to-do-dtos.h"
#include <optional>

struct GetToDoByIdResponse {
    std::optional<ToDoDTO> todo;
};