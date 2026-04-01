#pragma once

#include "../include.hpp"

class Client;

class ARegisterCommand
{
public:
    virtual void executeCommand(Client& client, int fd, std::vector<std::string>& message) = 0;
};