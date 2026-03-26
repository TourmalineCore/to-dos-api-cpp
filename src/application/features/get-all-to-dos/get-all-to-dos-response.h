#pragma once
#include "../../shared-dtos/to-do-dtos.h"
#include <vector>

struct GetAllToDosResponse {
    std::vector<ToDoDTO> todos;
};