#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class SimpleController : public drogon::HttpController<SimpleController> {
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(SimpleController::simpleGet, "/test", Get);
    // ADD_METHOD_TO(SimpleController::simpleGetQuery, "/test", Get);
    ADD_METHOD_TO(SimpleController::simplePost, "/test", Post);
    ADD_METHOD_TO(SimpleController::simpleGetRoute, "/test/{1}", Get);
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

    
};