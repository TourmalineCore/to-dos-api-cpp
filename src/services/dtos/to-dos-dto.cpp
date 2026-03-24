#include "to-dos-dto.h"

Json::Value ToDoDTO::toJson() const
{
    Json::Value json;
    json["id"] = id;
    json["name"] = name;

    return json;
}