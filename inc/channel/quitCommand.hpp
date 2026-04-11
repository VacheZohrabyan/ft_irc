#pragma once

#include "../include.hpp"
#include "../utils.hpp"
#include "AChannelCommand.hpp"

class QuitChannelCommand : public AChannelCommand
{
public:
    QuitChannelCommand();
    ~QuitChannelCommand();
    
public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);
};