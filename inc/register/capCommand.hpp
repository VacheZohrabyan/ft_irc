#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "ARegisterCommand.hpp"

class Client;

class CapCommand : public ARegisterCommand
{
public:
    CapCommand();
    ~CapCommand();

public:
    void executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message);
};