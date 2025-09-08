#include "todo-query.h"
#include "data/models/odb-gen/to-do-odb.hxx"
#include <odb/transaction.hxx>
#include <memory>

void ToDoQuery::add_todo(const std::string& name, std::time_t createdAtUtc)
{
    ToDo todo(name, createdAtUtc);

    odb::transaction t(db_.begin());
    db_.persist(todo);
    t.commit();
}

std::shared_ptr<ToDo> ToDoQuery::get_todo_by_id(int id)
{
    odb::transaction t(db_.begin());

    odb::result<ToDo> r = db_.query<ToDo>(odb::query<ToDo>::id == id);

    std::shared_ptr<ToDo> todo;
    if (!r.empty())
        todo = std::make_shared<ToDo>(*r.begin());

    t.commit();
    return todo;
}
