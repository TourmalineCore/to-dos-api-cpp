#include "app-controller.h"
#include "data/db_connection.h"

// TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/25): Create http exception handler or generic class for handling that type of errors
HttpResponsePtr AppController::createInternalServerErrorResponse(const std::string& error) const
{
    Json::Value jsonResponse;
    jsonResponse["status"] = "Error";
    jsonResponse["message"] = "Internal server error";
    jsonResponse["error"] = error;

    auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
    resp->setStatusCode(k500InternalServerError);
    return resp;
}

AppController::AppController()
{
    db_ = std::move(DbConnection::get());
    queries_ = std::make_unique<ToDoQueries>(*db_);
    commands_ = std::make_unique<ToDoCommands>(*db_);
    todo_service_ = std::make_unique<ToDoService>(*queries_, *commands_);
}

void AppController::getToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value jsonResponse;

    try
    {
        auto resp = HttpResponse::newHttpJsonResponse(todo_service_->toJson());
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}

void AppController::addToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value jsonResponse;

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

        todo_service_->addToDo(json->get("name", "").asString());

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k201Created);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}

void AppController::completeToDos(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value jsonResponse;

    try
    {
        auto json = req->getJsonObject();

        if (!json || !json->isMember("toDosIds"))
        {
            Json::Value result;
            result["status"] = "error";
            result["message"] = "Invalid JSON";

            auto resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);

            return;
        }

        auto toDosIds = json->get("toDosIds", Json::Value(Json::arrayValue));

        for (const auto& id : toDosIds)
        {
            todo_service_->completeToDo(id.asInt());
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

void AppController::deleteToDo(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback)
{
    Json::Value jsonResponse;

    try
    {
        auto toDoIdStr = req->getParameter("toDoId");
        int toDoId = std::stoi(toDoIdStr);

        todo_service_->completeToDo(toDoId);

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch (const std::exception& e)
    {
        callback(createInternalServerErrorResponse(e.what()));
    }
}
