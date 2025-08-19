#pragma once

#include <drogon/drogon.h>

using namespace drogon;
 
class HeaderMiddleware : public HttpMiddleware<HeaderMiddleware>
{
public:
    HeaderMiddleware(){};

    void invoke(const HttpRequestPtr &req, MiddlewareNextCallback &&nextCb, MiddlewareCallback &&mcb) override;
};
