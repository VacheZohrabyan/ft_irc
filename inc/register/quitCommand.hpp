#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "ARegisterCommand.hpp"

class QuitRegisterCommand : public ARegisterCommand
{
public:
    QuitRegisterCommand();
    ~QuitRegisterCommand();
    
public:
    void executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message);
};