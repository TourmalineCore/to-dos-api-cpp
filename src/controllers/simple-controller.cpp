#include "simple-controller.h"

// Due to the way routes are processed in Drogon, there is no difference between Get and Get with query, so an additional handler is not used!
void SimpleController::simpleGet(const HttpRequestPtr& req,
                             std::function<void(const HttpResponsePtr&)>&& callback) {
    
    auto userId = req->getParameter("userId");
    auto name = req->getParameter("name");

    auto resp = drogon::HttpResponse::newHttpResponse();

    if (!userId.empty() || !name.empty()) {
        resp->setBody("Query params: userId=" + userId + ", name=" + name);
    } else {
        resp->setBody("GET /test without params");
    }

    callback(resp);
}

// void SimpleController::simpleGetQuery(const HttpRequestPtr& req,
//                                       std::function<void(const HttpResponsePtr&)>&& callback) {
//     auto userId = req->getParameter("userId");
//     auto name = req->getParameter("name");
//     auto resp = HttpResponse::newHttpResponse();
//     resp->setBody("GET /test with query: userId=" + userId + ", name=" + name);
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


