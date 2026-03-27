#include "create-to-do-handler.h"
#include <chrono>
#include <ctime>

using std::string;

CreateToDoResponse CreateToDoHandler::handle(const CreateToDoRequest& request)
{
    const std::time_t now_utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    const uint64_t id = _createToDoCommand.execute(request.name, now_utc);
    return { id };
}