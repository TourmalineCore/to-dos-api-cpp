#include "simple-controller.h"

#include <thread>
#include <chrono>
#include <coroutine>

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

void SimpleController::getTasks(const HttpRequestPtr& req,
                             std::function<void(const HttpResponsePtr&)>&& callback) {
    auto client = drogon::app().getDbClient("default");

    client->execSqlAsync(
        "SELECT id, description, is_done, created_at FROM tasks ORDER BY id",
        [callback](const drogon::orm::Result &r) {
            Json::Value tasks(Json::arrayValue);
            for (auto const &row : r) {
                Json::Value task;
                task["id"] = row["id"].as<int>();
                task["description"] = row["description"].as<std::string>();
                task["is_done"] = row["is_done"].as<bool>();
                task["created_at"] = row["created_at"].as<std::string>();
                tasks.append(task);
            }
            auto resp = HttpResponse::newHttpJsonResponse(tasks);
            callback(resp);
        },
        [callback](const drogon::orm::DrogonDbException &e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            resp->setBody(std::string("DB Error: ") + e.base().what());
            callback(resp);
        }
    );

    auto resp = HttpResponse::newHttpResponse();

    callback(resp);
}

void SimpleController::createTask(const HttpRequestPtr &req,
                           std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto json = req->getJsonObject();
    if (!json || !json->isMember("description")) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Missing 'description'");
        callback(resp);
        return;
    }

    std::string description = (*json)["description"].asString();

    auto client = drogon::app().getDbClient("default");

    client->execSqlAsync(
        "INSERT INTO tasks(description, is_done, created_at) VALUES($1, $2, NOW()) RETURNING id",
        [callback, description](const drogon::orm::Result &r) {
            Json::Value res;
            res["id"] = r[0]["id"].as<int>();
            res["description"] = description;
            res["is_done"] = false;
            auto resp = HttpResponse::newHttpJsonResponse(res);
            callback(resp);
        },
        [callback](const drogon::orm::DrogonDbException &e) {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k500InternalServerError);
            resp->setBody(std::string("DB Error: ") + e.base().what());
            callback(resp);
        },
        description, false
    );
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
