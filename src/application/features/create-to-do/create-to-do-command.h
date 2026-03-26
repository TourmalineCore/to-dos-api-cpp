#pragma once

#include "to-do.h"
#include <memory>
#include <odb/database.hxx>

class CreateToDoCommand
{
public:
    CreateToDoCommand(odb::database& db)
    : db_(db)
    {}

    uint64_t execute(const std::string& name, std::time_t createdAtUtc);

private:
    odb::database& db_;
};