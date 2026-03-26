#include "soft-delete-to-do-handler.h"

// TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/38): add here a check for not found todo
SoftDeleteToDoResponse SoftDeleteToDoHandler::handle(uint64_t id)
{
    const uint64_t deletedId = _softDeleteToDoCommand.execute(static_cast<int>(id));
    return { deletedId };
}