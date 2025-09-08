#include "to-dos.service.h"

Json::Value ToDo::toJson() const {
    Json::Value json;
    json["id"] = id;
    json["description"] = description;

    return json;
}

void ToDos::addToDo(const std::string description) {
    _toDos.push_back({
      _nextToDoId, 
      description
    });

    _nextToDoId++;
}

const std::vector<ToDo>& ToDos::getToDos() const {
    return _toDos;
}

Json::Value ToDos::toJson() const {
    Json::Value json;
    Json::Value toDosArray(Json::arrayValue);
    
    for (const auto& toDo : _toDos) {
        toDosArray.append(toDo.toJson());
    }
    
    json["toDos"] = toDosArray;

    return json;
}

bool ToDos::completeToDo(int id) {
    for (auto it = _toDos.begin(); it != _toDos.end(); ++it) {
        if (it->id == id) {
            _toDos.erase(it);

            return true;
        }
    }

    return false;
}