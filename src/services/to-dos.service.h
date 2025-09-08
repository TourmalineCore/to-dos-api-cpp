#pragma once

#include <string>
#include <vector>
#include <json/json.h>

struct ToDo {
    int id;
    std::string description;

    Json::Value toJson() const;
};

class ToDos {
  private:
    std::vector<ToDo> _toDos{
      { 0, "Read TDD book" },
      { 1, "Read Mobx & React basic docs" },
      { 2, "Explore Cypress" },
    };

    int _nextToDoId = 3;

  public:
    ToDos() = default;

    void addToDo(const std::string description);

    bool completeToDo(int id);

    const std::vector<ToDo>& getToDos() const;

    Json::Value toJson() const;
};