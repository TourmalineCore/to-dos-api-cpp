#include "to-dos-dto.h"

Json::Value ToDoDTO::toJson() const {
    Json::Value json;
    json["id"] = id;
    json["description"] = description;

    return json;
}