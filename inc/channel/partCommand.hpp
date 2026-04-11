#pragma once

#include "../../inc/include.hpp"
#include "../../inc/channel/AChannelCommand.hpp"
#include "../../inc/utils.hpp"

class PartCommand : public AChannelCommand
{
public:
    PartCommand();
    ~PartCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);
};