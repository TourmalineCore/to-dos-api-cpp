#include "header-middleware.h"

void HeaderMiddleware::invoke(const HttpRequestPtr &req, MiddlewareNextCallback &&nextCb, MiddlewareCallback &&mcb)
{
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->addHeader("Custom-Header-From-Middleware", "some text");

    mcb(resp);
}