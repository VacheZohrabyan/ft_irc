#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "AMessageCommand.hpp"

class QuitMessageCommand : public AMessageCommand
{
public:
    QuitMessageCommand();
    ~QuitMessageCommand();
    
public:
    void executeCommand(Client& client, std::map<int, Client>& clients, Chanel& chanel, int fd, std::vector<std::string>& message);
};