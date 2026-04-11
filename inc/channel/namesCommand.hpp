#pragma once

#include "../../inc/include.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/channel/AChannelCommand.hpp"

class NamesCommand : public AChannelCommand
{
public:
    NamesCommand();
    ~NamesCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);
};