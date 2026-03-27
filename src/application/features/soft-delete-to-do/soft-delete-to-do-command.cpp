#include "soft-delete-to-do-command.h"
#include "odb-gen/to-do-odb.hxx"
#include <chrono>
#include <memory>
#include <odb/transaction.hxx>

uint64_t SoftDeleteCommand::execute(int id)
{
    odb::transaction t(db_.begin());

    std::unique_ptr<ToDo> todo(db_.load<ToDo>(id));
    const std::time_t now_utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    todo->deletedAtUtc(now_utc);
    db_.update(*todo);

    t.commit();
    return todo->id();
}