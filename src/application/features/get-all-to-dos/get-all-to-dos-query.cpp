#include "get-all-to-dos-query.h"
#include "odb-gen/to-do-odb.hxx"
#include <odb/transaction.hxx>

std::shared_ptr<std::vector<ToDo>> GetAllToDosQuery::get()
{
    odb::transaction transaction(db_.begin());

    odb::result<ToDo> query_result = db_.query<ToDo>(odb::query<ToDo>());

    auto todos = std::make_shared<std::vector<ToDo>>();
    for (auto i = query_result.begin(); i != query_result.end(); ++i)
        todos->push_back(*i);

    transaction.commit();
    return todos;
}