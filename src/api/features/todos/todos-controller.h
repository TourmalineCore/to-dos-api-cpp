#pragma once

#include <drogon/HttpController.h>

#include "features/create-to-do/create-to-do-handler.h"
#include "features/get-all-to-dos/get-all-to-dos-handler.h"
#include "features/get-to-do-by-id/get-to-do-by-id-handler.h"
#include "features/hard-delete-to-do/hard-delete-to-do-handler.h"
#include "features/soft-delete-to-do/soft-delete-to-do-handler.h"

using namespace drogon;

class ToDosController : public drogon::HttpController<ToDosController>
{
public:
    explicit ToDosController();

    METHOD_LIST_BEGIN
    ADD_METHOD_TO(AppController::getToDos, "/api/to-dos", Get);                 // Getting a list of tasks
    ADD_METHOD_TO(AppController::addToDo, "/api/to-dos", Post);                 // Adding a new task
    ADD_METHOD_TO(AppController::completeToDos, "/api/to-dos/complete", Post);  // Executing (deleting) a task list
    ADD_METHOD_TO(AppController::deleteToDo, "/api/to-dos", Delete);            // Deleting a specific task
    METHOD_LIST_END

    HttpResponsePtr createInternalServerErrorResponse(const std::string& error) const;

    void getToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void addToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void completeToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

    void deleteToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback);

private:
    std::shared_ptr<odb::database> db_;

    std::unique_ptr<CreateToDoCommand> createToDoCommand_;
    std::unique_ptr<GetAllToDosQuery> getAllToDosQuery_;
    std::unique_ptr<GetToDoById> getToDoByIdQuery_;
    std::unique_ptr<HardDeleteToDoCommand> hardDeleteToDoCommand_;
    std::unique_ptr<SoftDeleteCommand> softDeleteCommand_;

    std::unique_ptr<CreateToDoHandler> createToDoHandler_;
    std::unique_ptr<GetAllToDosHandler> getAllToDosHandler_;
    std::unique_ptr<GetToDoByIdHandler> getToDoByIdHandler_;
    std::unique_ptr<HardDeleteToDoHandler> hardDeleteToDoHandler_;
    std::unique_ptr<SoftDeleteToDoHandler> softDeleteToDoHandler_;
};