#include "get-to-do-by-id-query.h"
#include "odb-gen/to-do-odb.hxx"
#include <memory>
#include <odb/transaction.hxx>

std::shared_ptr<ToDo> GetToDoById::get(int id)
{
    odb::transaction t(db_.begin());

    odb::result<ToDo> r = db_.query<ToDo>(odb::query<ToDo>::id == id);

    std::shared_ptr<ToDo> todo;
    if (!r.empty())
        todo = std::make_shared<ToDo>(*r.begin());

    t.commit();
    return todo;
}