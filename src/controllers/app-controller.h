#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class AppController : public drogon::HttpController<AppController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AppController::getToDos, "/to-dos", Get); // Getting a list of tasks
    ADD_METHOD_TO(AppController::addToDo, "/to-dos", Post); // Adding a new task
    ADD_METHOD_TO(AppController::completeToDos, "/to-dos/complete", Post); // Executing (deleting) a task list
    ADD_METHOD_TO(AppController::deleteToDo, "/to-dos", Delete); // Deleting a specific task
    METHOD_LIST_END

    void getToDos(const HttpRequestPtr& req, 
        std::function<void(const HttpResponsePtr&)>&& callback);
    
    void addToDo(const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback);

    void completeToDos(const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback);
    
    void deleteToDo(const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback);
};