#pragma once
#include "soft-delete-to-do-command.h"
#include "soft-delete-to-do-response.h"
#include <cstdint>

class SoftDeleteToDoHandler
{
private:
    SoftDeleteCommand& _softDeleteToDoCommand;

public:
    explicit SoftDeleteToDoHandler(SoftDeleteCommand& softDeleteToDoCommand)
    : _softDeleteToDoCommand(softDeleteToDoCommand)
    {}

    SoftDeleteToDoResponse handle(std::uint64_t id);
};