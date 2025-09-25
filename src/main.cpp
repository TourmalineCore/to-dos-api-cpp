#include "data/commands/todo-commands.h"
#include "data/queries/todo-queries.h"
#include <ctime>
#include <drogon/HttpAppFramework.h>
#include <iomanip>
#include <iostream>
#include <odb/pgsql/database.hxx>
#include <string>
#include <vector>

int main()
{
    drogon::app().addListener("127.0.0.1", 8080);
    drogon::app().run();

    return 0;
}
