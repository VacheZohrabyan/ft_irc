#include "../../inc/administration/whoisCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/channel/chanel.hpp"

WhoisCommand::WhoisCommand()
{

}

WhoisCommand::~WhoisCommand()
{

}

void WhoisCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    int fdClient = findClientFd(message[1], clients);
    if (fdClient == -1)
        return Utils::errorNoNickNameGiven(fd);
    std::map<int, Client>::const_iterator itClient = clients.find(fdClient);
    std::string tmpMsg = ":localhost 311 " + client.getNick() + " " + itClient->second.getNick() + " " + itClient->second.getUser() + " " + itClient->second.getHost() + " * :" + itClient->second.getReal() + "\r\n";
    Utils::sendMessage(fd, tmpMsg);
    tmpMsg = ":localhost 312 " + client.getNick() + " " + itClient->second.getNick() + " localhost :School 42Yerevan IRC Server\r\n"; 
    Utils::sendMessage(fd, tmpMsg);
    std::string chanelName;
    for (std::map<std::string, Chanel>::const_iterator itChanel = chanels.begin(); itChanel != chanels.end(); ++itChanel)
    {
        if (!itChanel->second.hasClient(itClient->second.getNick()))
            continue;
        chanelName += itChanel->first;
        chanelName += " ";
    }
    if (!chanelName.empty())
    {
        tmpMsg = ":localhost 319 " + client.getNick() + " " + itClient->second.getNick() + " :@" + chanelName + "\r\n";
        Utils::sendMessage(fd, tmpMsg);
    }
    tmpMsg = ":localhost 318 " + client.getNick() + itClient->second.getNick() + " :End of /WHOIS list\r\n";
    Utils::sendMessage(fd, tmpMsg);
}

int WhoisCommand::findClientFd(const std::string& nick, const std::map<int, Client>& clients) const
{
    for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return it->first;
    }
    return -1;
}