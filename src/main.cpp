#include "data/queries/todo-query.h"
#include <vector>
#include <string>
#include <odb/pgsql/database.hxx>
#include <iostream>

int main() {
    try
    {
        const std::string user     = "postgres";
        const std::string password = "postgres";
        const std::string db_name  = "postgres";
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

        ToDoQuery todo_query(*db);

        std::time_t now = std::time(nullptr);
        todo_query.add_todo("Checking of ODB", now);

        std::shared_ptr<ToDo> todo = todo_query.get_todo_by_id(1);

        if (todo)
        {
            std::cout << "Found TODO:" << std::endl;
            std::cout << "ID: " << todo->id() << std::endl;
            std::cout << "Name: " << todo->name() << std::endl;
            std::cout << "Created At (timestamp): " << todo->createdAtUtc() << std::endl;
        }
        else
        {
            std::cout << "TODO with id=1 not found" << std::endl;
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

    return 0;
}
