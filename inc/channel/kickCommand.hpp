#pragma once

#include "../../inc/channel/AChannelCommand.hpp"

class Client;
class Chanel;

class KickCommand : public AChannelCommand
{
public:
    KickCommand();
    ~KickCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);

private:
    std::string concatMessage(const std::vector<std::string>& message) const;
    int findClient(const std::string& nick, const std::map<int, Client>& clients) const;
};