#include "hard-delete-to-do-handler.h"

// TODO(https://github.com/TourmalineCore/to-dos-api-cpp/issues/38): add here a check for not found todo
bool HardDeleteToDoHandler::handle(std::uint64_t id)
{
    (void) _hardDeleteToDoCommand.execute(static_cast<std::uint64_t>(id));
    return true;
}