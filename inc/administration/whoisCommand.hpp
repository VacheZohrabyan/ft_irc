#pragma once

#include "../../inc/include.hpp"
#include "../../inc/administration/AAdministrationCommand.hpp"

class Client;
class Chanel;

class WhoisCommand : public AAdministrationCommand
{
public:
    WhoisCommand();
    ~WhoisCommand();

public:
    void executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients);

private:
    int findClientFd(const std::string& nick, const std::map<int, Client>& clients) const;
};