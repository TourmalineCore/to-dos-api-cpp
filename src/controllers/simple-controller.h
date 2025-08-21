#pragma once

#include <drogon/HttpController.h>
#include "filters/auth-filter.h"

using namespace drogon;

class SimpleController : public drogon::HttpController<SimpleController> {
public:
    // METHOD_ADD - namespace and the controller class name are added to the route
    // ADD_METHOD_TO - absolute path from the parameters are added to the route
    METHOD_LIST_BEGIN
    // Filter only preprocessing, middleware more global processing in middle of controller work or postprocess
    ADD_METHOD_TO(SimpleController::simpleGet, "/test", Get, "AuthFilter", "HeaderMiddleware");
    // ADD_METHOD_TO(SimpleController::simpleGetQuery, "/test", Get);
    ADD_METHOD_TO(SimpleController::simplePost, "/test", Post);
    ADD_METHOD_TO(SimpleController::simpleGetRoute, "/test/{1}", Get);
    ADD_METHOD_TO(SimpleController::concurrencyTest, "/concurrency-test", Get);
    ADD_METHOD_TO(SimpleController::asyncTest, "/async-test", Get);
    METHOD_LIST_END

    // Due to the way routes are processed in Drogon, there is no difference between Get and Get with query, so an additional handler is not used!
    void simpleGet(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback);

    // void simpleGetQuery(const HttpRequestPtr& req,
    //            std::function<void(const HttpResponsePtr&)>&& callback);

    void simplePost(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback);

    void simpleGetRoute(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback, uint32_t id);

    void concurrencyTest(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback);

    void asyncTest(const HttpRequestPtr& req,
               std::function<void(const HttpResponsePtr&)>&& callback);
};