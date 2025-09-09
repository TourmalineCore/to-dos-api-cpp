#pragma once

#include "dtos/to-dos-dto.h"

#include <vector>
#include <json/json.h>

class ToDoService
{
private:
  std::vector<ToDoDTO> _toDos{
      {0, "Read TDD book"},
      {1, "Read Mobx & React basic docs"},
      {2, "Explore Cypress"},
  };

  int _nextToDoId = 3;

public:
  ToDoService() = default;

  void addToDo(const std::string description);

  bool completeToDo(int id);

  const std::vector<ToDoDTO> &getToDos() const;

  Json::Value toJson() const;
};