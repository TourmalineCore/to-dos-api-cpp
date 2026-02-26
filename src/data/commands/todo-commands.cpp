#include "todo-commands.h"
#include "data/models/odb-gen/to-do-odb.hxx"
#include <memory>
#include <odb/transaction.hxx>

uint64_t ToDoCommands::create_todo(const std::string& name, std::time_t createdAtUtc)
{
    ToDo todo(name, createdAtUtc);

    odb::transaction t(db_.begin());
    db_.persist(todo);
    t.commit();

    return todo.id();
}

uint64_t ToDoCommands::delete_todo(int id)
{
    odb::transaction t(db_.begin());

    const unsigned long long todo_id = db_.erase_query<ToDo>(odb::query<ToDo>::id == id);

    t.commit();
    // TODO: return exactly deleted todo id
    return id;
}

uint64_t ToDoCommands::soft_delete_todo(int id)
{
    odb::transaction t(db_.begin());

    std::unique_ptr<ToDo> todo(db_.load<ToDo>(id));

    const std::time_t now_utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    todo->deletedAtUtc(now_utc);
    db_.update(*todo);

    t.commit();
    return todo->id();
}
