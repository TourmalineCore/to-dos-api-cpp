#include "get-to-do-by-id-query.h"
#include "odb-gen/to-do-odb.hxx"
#include <memory>
#include <odb/transaction.hxx>

std::shared_ptr<ToDo> GetToDoById::get(int id)
{
    odb::transaction transaction(db_.begin());

    odb::result<ToDo> query_result = db_.query<ToDo>(odb::query<ToDo>::id == id);

    std::shared_ptr<ToDo> todo;
    if (!query_result.empty())
        todo = std::make_shared<ToDo>(*query_result.begin());

    transaction.commit();
    return todo;
}