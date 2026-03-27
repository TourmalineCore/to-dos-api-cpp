#pragma once
#include "hard-delete-to-do-command.h"
#include <cstdint>

class HardDeleteToDoHandler
{
private:
    HardDeleteToDoCommand& _hardDeleteToDoCommand;

public:
    explicit HardDeleteToDoHandler(HardDeleteToDoCommand& hardDeleteToDoCommand)
    : _hardDeleteToDoCommand(hardDeleteToDoCommand)
    {}

    bool handle(uint64_t id);
};