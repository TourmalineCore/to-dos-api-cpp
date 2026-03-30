#include "todos-controller.h"
#include "db_connection.h"

// TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/25): Create http exception handler or generic class for handling that type of errors
HttpResponsePtr ToDosController::createInternalServerErrorResponse(const std::string& error) const
{
    Json::Value jsonResponse;
    jsonResponse["status"] = "Error";
    jsonResponse["message"] = "Internal server error";
    jsonResponse["error"] = error;

    auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
    resp->setStatusCode(k500InternalServerError);
    return resp;
}

ToDosController::ToDosController()
{
    db_ = std::move(DbConnection::get());

    createToDoCommand_ = std::make_unique<CreateToDoCommand>(*db_);
    getAllToDosQuery_ = std::make_unique<GetAllToDosQuery>(*db_);
    getToDoByIdQuery_ = std::make_unique<GetToDoById>(*db_);
    hardDeleteToDoCommand_ = std::make_unique<HardDeleteToDoCommand>(*db_);
    softDeleteCommand_ = std::make_unique<SoftDeleteCommand>(*db_);

    createToDoHandler_ = std::make_unique<CreateToDoHandler>(*createToDoCommand_);
    getAllToDosHandler_ = std::make_unique<GetAllToDosHandler>(*getAllToDosQuery_);
    getToDoByIdHandler_ = std::make_unique<GetToDoByIdHandler>(*getToDoByIdQuery_);
    hardDeleteToDoHandler_ = std::make_unique<HardDeleteToDoHandler>(*hardDeleteToDoCommand_);
    softDeleteToDoHandler_ = std::make_unique<SoftDeleteToDoHandler>(*softDeleteCommand_);
}

void ToDosController::getToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    try
    {
        auto result = getAllToDosHandler_->handle();

        Json::Value toDosArray(Json::arrayValue);
        for (const auto& dto : result.todos)
            toDosArray.append(dto.toJson());

        Json::Value json;
        json["toDos"] = toDosArray;

        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}

void ToDosController::addToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    try
    {
        auto json = req->getJsonObject();

        if (!json || !json->isMember("name"))
        {
            Json::Value result;
            result["status"] = "error";
            result["message"] = "Invalid JSON";

            auto resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }

        CreateToDoRequest request { json->get("name", "").asString() };
        (void) createToDoHandler_->handle(request);

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k201Created);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}

void ToDosController::completeToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    try
    {
        auto json = req->getJsonObject();

        if (!json || !json->isMember("toDoIds"))
        {
            Json::Value result;
            result["status"] = "error";
            result["message"] = "Invalid JSON";

            auto resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }

        auto toDosIds = json->get("toDoIds", Json::Value(Json::arrayValue));
        for (const auto& id : toDosIds)
        {
            // TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/38): add here a check for not found todos
            (void) softDeleteToDoHandler_->handle(static_cast<std::uint64_t>(id.asInt()));
        }

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}

void ToDosController::deleteToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    try
    {
        auto toDoIdStr = req->getParameter("toDoId");
        const std::uint64_t toDoId = static_cast<std::uint64_t>(std::stoi(toDoIdStr));

        // TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/38): add here a check for not found todo
        (void) hardDeleteToDoHandler_->handle(toDoId);

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}