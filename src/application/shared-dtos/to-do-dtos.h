#pragma once
#include <json/json.h>
#include <string>

struct ToDoDTO
{
    std::uint64_t id;
    std::string name;

    Json::Value toJson() const;
};