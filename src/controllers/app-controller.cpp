#include "app-controller.h"
#include "../services/to-dos.service.h"

void AppController::getToDos(const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback) {
    Json::Value jsonResponse;

    try {
        ToDos toDos;

        auto resp = HttpResponse::newHttpJsonResponse(toDos.toJson());
        resp->setStatusCode(k200OK);
        callback(resp);

    } catch (const std::exception& e) {
        jsonResponse["status"] = "error";
        jsonResponse["message"] = "Internal server error";
        jsonResponse["error"] = e.what();
        
        auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}

void AppController::addToDo(const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback) {
    Json::Value jsonResponse;

    try {
        auto json = req->getJsonObject();

        if (!json || !json->isMember("description")) {
            Json::Value result;
            result["status"] = "error";
            result["message"] = "Invalid JSON";

            auto resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);

            return;
        }

        ToDos toDos;
        toDos.addToDo(json->get("description", "").asString());

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k201Created);
        callback(resp);
        
    } catch (const std::exception& e) {
        jsonResponse["status"] = "error";
        jsonResponse["message"] = "Internal server error";
        jsonResponse["error"] = e.what();
        
        auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}

void AppController::completeToDos(const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback) {
    Json::Value jsonResponse;

    try {
        auto json = req->getJsonObject();

        if (!json || !json->isMember("toDosIds")) {
            Json::Value result;
            result["status"] = "error";
            result["message"] = "Invalid JSON";

            auto resp = HttpResponse::newHttpJsonResponse(result);
            resp->setStatusCode(k400BadRequest);
            callback(resp);

            return;
        }

        ToDos toDos;
        auto toDosIds = json->get("toDosIds", Json::Value(Json::arrayValue));

        for (const auto& id : toDosIds) {
          toDos.completeToDo(id.asInt());
        }

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);

    } catch (const std::exception& e) {
        jsonResponse["status"] = "error";
        jsonResponse["message"] = "Internal server error";
        jsonResponse["error"] = e.what();
        
        auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}

void AppController::deleteToDo(const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback) {
    Json::Value jsonResponse;

    try {
        auto toDoIdStr = req->getParameter("toDoId");
        int toDoId = std::stoi(toDoIdStr);
        
        ToDos toDos;
        toDos.completeToDo(toDoId);

        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
        
    } catch (const std::exception& e) {
        jsonResponse["status"] = "error";
        jsonResponse["message"] = "Internal server error";
        jsonResponse["error"] = e.what();
        
        auto resp = HttpResponse::newHttpJsonResponse(jsonResponse);
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
    }
}
