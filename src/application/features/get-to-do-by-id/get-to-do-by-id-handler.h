#pragma once
#include "get-to-do-by-id-query.h"
#include "get-to-do-by-id-response.h"
#include <cstdint>

class GetToDoByIdHandler
{
private:
    GetToDoById& _getToDoByIdQuery;

public:
    explicit GetToDoByIdHandler(GetToDoById& getToDoByIdQuery)
    : _getToDoByIdQuery(getToDoByIdQuery)
    {}

    GetToDoByIdResponse handle(uint64_t id);
};