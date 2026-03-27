#pragma once
#include "get-all-to-dos-query.h"
#include "get-all-to-dos-response.h"

class GetAllToDosHandler
{
private:
    GetAllToDosQuery& _getAllToDosQuery;

public:
    explicit GetAllToDosHandler(GetAllToDosQuery& getAllToDosQuery)
    : _getAllToDosQuery(getAllToDosQuery)
    {}

    GetAllToDosResponse handle();
};