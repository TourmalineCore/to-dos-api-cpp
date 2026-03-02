#include <drogon/HttpAppFramework.h>

int main()
{
    drogon::app().addListener("0.0.0.0", 80);
    drogon::app().run();

    return 0;
}
