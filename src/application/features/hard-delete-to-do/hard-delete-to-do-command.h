#pragma once

#include "to-do.h"
#include <memory>
#include <odb/database.hxx>

class HardDeleteToDoCommand
{
public:
    HardDeleteToDoCommand(odb::database& db)
    : db_(db)
    {}

    std::uint64_t execute(int id);

private:
    odb::database& db_;
};