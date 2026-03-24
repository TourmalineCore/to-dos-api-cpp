#pragma once

#include <json/json.h>
#include <string>

struct ToDoDTO
{
    int id;
    std::string name;

    Json::Value toJson() const;
};