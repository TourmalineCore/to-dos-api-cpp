#include "get-all-to-dos-query.h"
#include "odb-gen/to-do-odb.hxx"
#include <odb/transaction.hxx>

std::shared_ptr<std::vector<ToDo>> GetAllToDosQuery::get()
{
    odb::transaction t(db_.begin());

    odb::result<ToDo> r = db_.query<ToDo>(odb::query<ToDo>());

    auto todos = std::make_shared<std::vector<ToDo>>();
    for (auto i = r.begin(); i != r.end(); ++i)
        todos->push_back(*i);

    t.commit();
    return todos;
}