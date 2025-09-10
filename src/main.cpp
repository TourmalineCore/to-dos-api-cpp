#include <drogon/HttpAppFramework.h>

int main() {
    drogon::app().addListener("127.0.0.1", 8080);
    drogon::app().run();

    return 0;
}
