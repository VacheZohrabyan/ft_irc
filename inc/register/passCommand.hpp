#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "ARegisterCommand.hpp"

class Client;

class PassCommand : public ARegisterCommand
{
public:
    PassCommand();
    ~PassCommand();

public:
    void executeCommand(Client& client, int fd, std::vector<std::string>& message);
};