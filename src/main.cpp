#include "data/queries/todo-queries.h"
#include "data/commands/todo-commands.h"
#include <drogon/HttpAppFramework.h>
#include <vector>
#include <string>
#include <odb/pgsql/database.hxx>
#include <iostream>
#include <iomanip>
#include <ctime>

int main() {
    try
    {
        // TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/22): parse that variables from .env or .env.dev 
        const std::string user     = "postgres";
        const std::string password = "admin";
        const std::string db_name  = "to-dos-api-cpp_db";
        const std::string host     = "localhost";
        const unsigned    port     = 5432;

        std::string conninfo = 
            "host="     + host +
            " port="    + std::to_string(port) +
            " dbname="  + db_name +
            " user="    + user +
            " password="+ password;

        std::unique_ptr<odb::database> db(
            new odb::pgsql::database(conninfo)
        );

        ToDoQueries todo_queries(*db);
        ToDoCommands todo_commands(*db);
        const std::time_t now_utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        uint64_t added_todo = todo_commands.create_todo("random_todo", now_utc);
        std::cout << "Added TODO:" <<  added_todo << std::endl;
        uint64_t soft_removed_todo = todo_commands.soft_delete_todo(added_todo);
        std::cout << "Soft Removed TODO:" <<  soft_removed_todo << std::endl;
        uint64_t removed_todo = todo_commands.delete_todo(added_todo);
        std::cout << "Removed TODO:" <<  removed_todo << std::endl;

        std::shared_ptr<std::vector<ToDo>> todos = todo_queries.get_all_todos();
        std::shared_ptr<ToDo> todo = todo_queries.get_todo_by_id(1);


        if (todos && todo)
        {
            std::cout << "Found TODOs:" <<  todos->size() << std::endl;
            const std::time_t t = todo->createdAtUtc();
            std::tm tm{};
            gmtime_r(&t, &tm);
            std::cout << "Found TODO id:" << todo->id() << " createdAtUtc: " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S UTC") << std::endl;
        }
        else
        {
            std::cout << "TODO or TODOs not founded" << std::endl;
        }
    }
    catch (const odb::exception& e)
    {
        std::cerr << "Error ODB: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    drogon::app().addListener("127.0.0.1", 8080);
    drogon::app().run();

    return 0;
}
