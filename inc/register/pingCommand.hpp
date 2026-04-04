#pragma once

#include "../include.hpp"
#include "ARegisterCommand.hpp"
#include "../utils.hpp"

class client;

class PingCommand : public ARegisterCommand
{
public:
    PingCommand();
    ~PingCommand();

public:
    void executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message);
};