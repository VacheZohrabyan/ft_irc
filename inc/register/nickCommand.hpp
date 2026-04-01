#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "ARegisterCommand.hpp"

class Client;

class NickCommand : public ARegisterCommand
{
public:
    NickCommand();
    ~NickCommand();

public:
    void executeCommand(Client& client, int fd, std::vector<std::string>& message);
};