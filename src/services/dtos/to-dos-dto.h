#pragma once

#include <string>
#include <json/json.h>

struct ToDoDTO
{
  int id;
  std::string description;

  Json::Value toJson() const;
};