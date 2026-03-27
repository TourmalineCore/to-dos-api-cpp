#include "to-do-dtos.h"

Json::Value ToDoDTO::toJson() const
{
    Json::Value json;
    json["id"] = id;
    json["name"] = name;
    return json;
}