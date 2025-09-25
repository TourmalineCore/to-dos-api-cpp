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
    try
    {
        // TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/27): add migration update on startup

        const std::string user = std::getenv("POSTGRES_USER");
        const std::string password = std::getenv("POSTGRES_PASSWORD");
        const std::string db_name = std::getenv("POSTGRES_DB");
        const std::string host = std::getenv("POSTGRES_HOST");
        const std::string port = std::getenv("POSTGRES_PORT");

        std::string conninfo = "host=" + host + " port=" + port + " dbname=" + db_name + " user=" + user + " password=" + password;

        std::unique_ptr<odb::database> db(new odb::pgsql::database(conninfo));

        ToDoQueries todo_queries(*db);
        ToDoCommands todo_commands(*db);
        const std::time_t now_utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        uint64_t added_todo = todo_commands.create_todo("random_todo", now_utc);
        std::cout << "Added TODO:" << added_todo << std::endl;
        uint64_t soft_removed_todo = todo_commands.soft_delete_todo(added_todo);
        std::cout << "Soft Removed TODO:" << soft_removed_todo << std::endl;
        uint64_t removed_todo = todo_commands.delete_todo(added_todo);
        std::cout << "Removed TODO:" << removed_todo << std::endl;

        std::shared_ptr<std::vector<ToDo>> todos = todo_queries.get_all_todos();
        std::shared_ptr<ToDo> todo = todo_queries.get_todo_by_id(1);


        if (todos && todo)
        {
            std::cout << "Found TODOs:" << todos->size() << std::endl;
            const std::time_t t = todo->createdAtUtc();
            std::tm tm {};
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
