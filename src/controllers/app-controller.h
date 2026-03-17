#pragma once

#include <drogon/HttpController.h>

#include "app-config.h"
#include "data/commands/todo-commands.h"
#include "data/queries/todo-queries.h"
#include "services/to-dos.service.h"

const APP_CONTROLLER_BASE_PREFIX = AppConfig::apiGlobalPrefix() + "/to-dos";

using namespace drogon;

class AppController : public drogon::HttpController<AppController>
{
public:
    explicit AppController();

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AppController::getToDos, APP_CONTROLLER_BASE_PREFIX, Get);                    // Getting a list of tasks
    ADD_METHOD_TO(AppController::addToDo, APP_CONTROLLER_BASE_PREFIX, Post);                    // Adding a new task
    ADD_METHOD_TO(AppController::completeToDos, APP_CONTROLLER_BASE_PREFIX "/complete", Post);  // Executing (deleting) a task list
    ADD_METHOD_TO(AppController::deleteToDo, APP_CONTROLLER_BASE_PREFIX, Delete);               // Deleting a specific task
    METHOD_LIST_END

    HttpResponsePtr createInternalServerErrorResponse(const std::string& error) const;

    void getToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void addToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void completeToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void deleteToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

private:
    std::shared_ptr<odb::database> db_;
    std::unique_ptr<ToDoQueries> queries_;
    std::unique_ptr<ToDoCommands> commands_;
    std::unique_ptr<ToDoService> todo_service_;
};