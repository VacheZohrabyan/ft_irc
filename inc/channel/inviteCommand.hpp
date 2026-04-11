#pragma once

#include "../../inc/include.hpp"
#include "../../inc/channel/AChannelCommand.hpp"

class Client;
class Chanel;

class InviteCommand : public AChannelCommand
{
public:
    InviteCommand();
    ~InviteCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);

private:
    bool findNick(const std::string& nick, const std::map<int, Client>& clients);
    const Client& findClient(const std::string nick, const std::map<int, Client>& clients);
};