#include "create-to-do-command.h"
#include "odb-gen/to-do-odb.hxx"
#include <odb/transaction.hxx>

std::uint64_t CreateToDoCommand::execute(const std::string& name, std::time_t createdAtUtc)
{
    ToDo todo(name, createdAtUtc);

    odb::transaction transaction(db_.begin());
    db_.persist(todo);
    transaction.commit();

    return todo.id();
}