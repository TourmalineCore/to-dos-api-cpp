#include "todo-queries.h"
#include "data/models/odb-gen/to-do-odb.hxx"
#include <odb/transaction.hxx>
#include <memory>

std::shared_ptr<std::vector<ToDo>> ToDoQueries::get_all_todos()
{
    odb::transaction t(db_.begin());

    odb::result<ToDo> r = db_.query<ToDo>(odb::query<ToDo>());

    auto todos = std::make_shared<std::vector<ToDo>>();
    for (auto i = r.begin(); i != r.end(); ++i)
        todos->push_back(*i);

    t.commit();
    return todos;
}

std::shared_ptr<ToDo> ToDoQueries::get_todo_by_id(int id)
{
    odb::transaction t(db_.begin());

    odb::result<ToDo> r = db_.query<ToDo>(odb::query<ToDo>::id == id);

    std::shared_ptr<ToDo> todo;
    if (!r.empty())
        todo = std::make_shared<ToDo>(*r.begin());

    t.commit();
    return todo;
}
