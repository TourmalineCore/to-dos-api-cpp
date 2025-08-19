#pragma once

#include <drogon/drogon.h>
using namespace drogon;

class AuthFilter : public HttpFilter<AuthFilter> {
public:
    AuthFilter() = default;

    virtual void doFilter(const HttpRequestPtr &request, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};