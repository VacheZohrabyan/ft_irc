#pragma once

#include "../include.hpp"

class Client;

class ARegisterCommand
{
public:
    virtual ~ARegisterCommand() { }
public:
    virtual void executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message) = 0;
};