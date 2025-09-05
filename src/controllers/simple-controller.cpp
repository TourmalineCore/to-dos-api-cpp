#include "simple-controller.h"

#include "models/Tasks.h"
#include "models/Users.h"

#include <drogon/orm/Mapper.h>

#include <thread>
#include <chrono>
#include <coroutine>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

// Due to the way routes are processed in Drogon, there is no difference between Get and Get with query, so an additional handler is not used!
void SimpleController::simpleGet(const HttpRequestPtr& req,
                             std::function<void(const HttpResponsePtr&)>&& callback) {
    
    auto user_id = req->getParameter("user_id");
    auto name = req->getParameter("name");

    auto resp = HttpResponse::newHttpResponse();

    if (!user_id.empty() || !name.empty()) {
        resp->setBody("Query params: user_id=" + user_id + ", name=" + name);
    } else {
        resp->setBody("GET /test without params");
    }

    callback(resp);
}

// void SimpleController::simpleGetQuery(const HttpRequestPtr& req,
//                                       std::function<void(const HttpResponsePtr&)>&& callback) {
//     auto user_id = req->getParameter("user_id");
//     auto name = req->getParameter("name");
//     auto resp = HttpResponse::newHttpResponse();
//     resp->setBody("GET /test with query: user_id=" + user_id + ", name=" + name);
//     callback(resp);
// }

void SimpleController::simplePost(const HttpRequestPtr& req,
                              std::function<void(const HttpResponsePtr&)>&& callback) {
    auto resp = HttpResponse::newHttpResponse();
    auto body = req->getBody();
    resp->setBody("POST /test, body: " + std::string(body));
    callback(resp);
}

void SimpleController::simpleGetRoute(const HttpRequestPtr& req,
                                   std::function<void(const HttpResponsePtr&)>&& callback,
                                   uint32_t id) {
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("GET /test/" + std::to_string(id));
    callback(resp);
}

void SimpleController::concurrencyTest(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback) {
    
    auto thread_id = std::this_thread::get_id();
    std::cout << "Handling request in thread ID: " << thread_id << std::endl;

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody("Thread ID: " + std::to_string(std::hash<std::thread::id>{}(thread_id)));
    callback(resp);
}

std::string simpleAsync()
{
    std::cout << "This Log from thread with id: " << std::this_thread::get_id() << std::endl;

    return "Done";
}

void SimpleController::asyncTest(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback)
{
    std::future<std::string> result = std::async(simpleAsync);
    simpleAsync();

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(result.get());

    callback(resp);
}

void SimpleController::getTasks(const HttpRequestPtr &req,
                            std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto dbClient = drogon::app().getDbClient();
    Mapper<Tasks> tasksMapper(dbClient);
    Mapper<Users> usersMapper(dbClient);

    tasksMapper.findAll(
    [callback](const std::vector<Tasks> &tasks) {
        Json::Value jsonTasksArray;

        for (const auto &task : tasks) {
            Json::Value jsonTask;
            jsonTask["id"] = task.getValueOfId();
            jsonTask["description"] = task.getValueOfDescription();
            jsonTask["status"] = task.getValueOfStatus();
            jsonTask["user_id"] = task.getValueOfUserId();
            jsonTask["created_at"] = task.getValueOfCreatedAt().toFormattedString(false);

            jsonTasksArray.append(jsonTask);
        }

        auto resp = HttpResponse::newHttpJsonResponse(jsonTasksArray);
        callback(resp);
    },
    [callback](const DrogonDbException &e) {
        Json::Value error;
        error["status"] = "error";
        error["message"] = e.base().what();

        auto resp = HttpResponse::newHttpJsonResponse(error);
        callback(resp);
    });
}

void SimpleController::getTaskById(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback,
                                   uint32_t id)
{
    auto dbClient = drogon::app().getDbClient();
    Mapper<Tasks> tasksMapper(dbClient);

    tasksMapper.findByPrimaryKey(id,
    [callback](const Tasks &task) {
        Json::Value jsonTask;
        jsonTask["id"] = task.getValueOfId();
        jsonTask["description"] = task.getValueOfDescription();
        jsonTask["status"] = task.getValueOfStatus();
        jsonTask["user_id"] = task.getValueOfUserId();
        jsonTask["created_at"] = task.getValueOfCreatedAt().toFormattedString(false);

        auto resp = HttpResponse::newHttpJsonResponse(jsonTask);
        callback(resp);
    },
    [callback](const DrogonDbException &e) {
        Json::Value error;
        error["status"] = "error";
        error["message"] = e.base().what();

        auto resp = HttpResponse::newHttpJsonResponse(error);
        callback(resp);
    });
}


void SimpleController::createTask(const HttpRequestPtr &req,
                           std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    Json::Value result;

    std::vector<std::string> requiredFields = {"description", "user_id"};
    std::vector<std::string> missingFields;

    if (!json) {
        result["status"] = "error";
        result["message"] = "Invalid JSON";
        auto resp = HttpResponse::newHttpJsonResponse(result);
        callback(resp);

        return;
    }

    for (const auto &field : requiredFields) {
        if (!json->isMember(field) || (*json)[field].isNull()) {
            missingFields.push_back(field);
        }
    }

    if (!missingFields.empty()) {
        result["status"] = "error";
        result["message"] = "Required fields are missing";
        result["missing"] = Json::arrayValue;

        for (const auto &field : missingFields) {
            result["missing"].append(field);
        }

        auto resp = HttpResponse::newHttpJsonResponse(result);
        callback(resp);

        return;
    }

    auto dbClient = drogon::app().getDbClient();
    Mapper<Tasks> tasksMapper(dbClient);

    Tasks newTask;
    newTask.setDescription(json->get("description", "").asString());
    newTask.setUserId(static_cast<int32_t>(json->get("user_id", 0).asInt()));

    tasksMapper.insert(newTask, 
    [callback](const Tasks &insertedTask) {
      Json::Value result;
      result["status"] = "OK";
      result["id"] = insertedTask.getValueOfId();

      auto resp = HttpResponse::newHttpJsonResponse(result);

      callback(resp);
    }, [callback](const DrogonDbException &e) {
      Json::Value error;
      error["status"] = "error";
      error["message"] = e.base().what();

      auto resp = HttpResponse::newHttpJsonResponse(error);
      callback(resp);
    });
}

void SimpleController::getUsers(const HttpRequestPtr &req,
                            std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto dbClient = drogon::app().getDbClient();
    Mapper<Users> usersMapper(dbClient);

    usersMapper.findAll(
    [callback](const std::vector<Users> &users) {
        Json::Value jsonUsersArray;

        for (const auto &user : users) {
            Json::Value jsonUser;
            jsonUser["id"] = user.getValueOfId();
            jsonUser["name"] = user.getValueOfName();
            jsonUser["surname"] = user.getValueOfSurname();
            jsonUser["email"] = user.getValueOfEmail();
            jsonUser["created_at"] = user.getValueOfCreatedAt().toFormattedString(false);

            jsonUsersArray.append(jsonUser);
        }

        auto resp = HttpResponse::newHttpJsonResponse(jsonUsersArray);
        callback(resp);
    },
    [callback](const DrogonDbException &e) {
        Json::Value error;
        error["status"] = "error";
        error["message"] = e.base().what();

        auto resp = HttpResponse::newHttpJsonResponse(error);
        callback(resp);
    });
}

void SimpleController::getUserById(const HttpRequestPtr &req,
                            std::function<void (const HttpResponsePtr &)> &&callback,
                            uint32_t id)
{
    auto dbClient = drogon::app().getDbClient();
    Mapper<Users> usersMapper(dbClient);

    usersMapper.findByPrimaryKey(id,
    [callback](const Users &user) {
        Json::Value jsonUser;
        jsonUser["id"] = user.getValueOfId();
        jsonUser["name"] = user.getValueOfName();
        jsonUser["surname"] = user.getValueOfSurname();
        jsonUser["email"] = user.getValueOfEmail();
        jsonUser["created_at"] = user.getValueOfCreatedAt().toFormattedString(false);

        auto resp = HttpResponse::newHttpJsonResponse(jsonUser);
        callback(resp);
    },
    [callback](const DrogonDbException &e) {
        Json::Value error;
        error["status"] = "error";
        error["message"] = e.base().what();

        auto resp = HttpResponse::newHttpJsonResponse(error);
        callback(resp);
    });
}

void SimpleController::createUser(const HttpRequestPtr &req,
                            std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    Json::Value result;

    std::vector<std::string> requiredFields = {"name", "surname"};
    std::vector<std::string> missingFields;

    if (!json) {
        result["status"] = "error";
        result["message"] = "Invalid JSON";
        auto resp = HttpResponse::newHttpJsonResponse(result);
        callback(resp);

        return;
    }

    for (const auto &field : requiredFields) {
        if (!json->isMember(field) || (*json)[field].isNull()) {
            missingFields.push_back(field);
        }
    }

    if (!missingFields.empty()) {
        result["status"] = "error";
        result["message"] = "Required fields are missing";
        result["missing"] = Json::arrayValue;

        for (const auto &field : missingFields) {
            result["missing"].append(field);
        }

        auto resp = HttpResponse::newHttpJsonResponse(result);
        callback(resp);

        return;
    }

    auto dbClient = drogon::app().getDbClient();
    Mapper<Users> usersMapper(dbClient);

    Users newUser;
    newUser.setName(json->get("name", "").asString());
    newUser.setSurname(json->get("surname", "").asString());

    if (!(*json)["email"].isNull()) {
        newUser.setEmail(json->get("email", "").asString());
    }

    usersMapper.insert(newUser, 
    [callback](const Users &insertedUser) {
      Json::Value result;
      result["status"] = "OK";
      result["id"] = insertedUser.getValueOfId();

      auto resp = HttpResponse::newHttpJsonResponse(result);

      callback(resp);
    }, [callback](const DrogonDbException &e) {
      Json::Value error;
      error["status"] = "error";
      error["message"] = e.base().what();

      auto resp = HttpResponse::newHttpJsonResponse(error);
      callback(resp);
    });
}

/*
  Coroutines in C++20 allow writing asynchronous or lazy computations. 
  Instead of returning a final result, a coroutine can suspend 
  execution (co_await, co_yield, co_return), transfer control back to the caller, 
  and later resume where it left off.

  Key operators:
    - co_return : completes the coroutine with a value.
    - co_yield  : produces a sequence of values, suspending between them.
    - co_await  : suspends until the awaited operation is ready.

  A coroutine must return a coroutine-aware type (like generator, task,
  or a custom promise type). These types manage suspension/resumption.

  Full explanation of them and example of usage here https://en.cppreference.com/w/cpp/language/coroutines.html
*/
