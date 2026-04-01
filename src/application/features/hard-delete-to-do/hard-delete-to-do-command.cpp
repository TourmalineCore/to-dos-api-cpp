#include "hard-delete-to-do-command.h"
#include "odb-gen/to-do-odb.hxx"
#include <odb/transaction.hxx>

std::uint64_t HardDeleteToDoCommand::execute(int id)
{
    odb::transaction transaction(db_.begin());
    const unsigned long long todo_id = db_.erase_query<ToDo>(odb::query<ToDo>::id == id);
    transaction.commit();

    // TODO: return exactly deleted todo id
    return id;
}