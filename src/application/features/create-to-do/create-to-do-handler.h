#pragma once
#include "create-to-do-command.h"
#include "create-to-do-request.h"
#include "create-to-do-response.h"

class CreateToDoHandler
{
private:
    CreateToDoCommand& _createToDoCommand;

public:
    explicit CreateToDoHandler(CreateToDoCommand& createToDoCommand)
    : _createToDoCommand(createToDoCommand)
    {}

    CreateToDoResponse handle(const CreateToDoRequest& request);
};