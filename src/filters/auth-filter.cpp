#include "auth-filter.h"

void AuthFilter::doFilter(const HttpRequestPtr &request, FilterCallback &&fcb, FilterChainCallback &&fccb){
    const std::string& authHeader = request->getHeader("Auth");

    if (authHeader.length() < 7)
    {
        Json::Value resultJson;
        resultJson["error"] = "No header authentication!";
        resultJson["status"] = 0;

        auto res = HttpResponse::newHttpJsonResponse(resultJson);
        res->setStatusCode(k401Unauthorized);
        return fcb(res);
    }

    return fccb();
}