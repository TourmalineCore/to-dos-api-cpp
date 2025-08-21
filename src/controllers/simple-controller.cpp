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


