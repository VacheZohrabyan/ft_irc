#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "ARegisterCommand.hpp"

class Client;

class CapCommand : public ARegisterCommand
{
public:
    CapCommand();
    virtual ~CapCommand();

public:
    void executeCommand(Client& client, int fd, std::vector<std::string>& message);
};