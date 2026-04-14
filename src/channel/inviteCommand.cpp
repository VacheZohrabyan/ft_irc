#include "../../inc/channel/inviteCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/chanel.hpp"

InviteCommand::InviteCommand()
{

}

InviteCommand::~InviteCommand()
{

}

void InviteCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    if (!findNick(message[1], clients))
        return Utils::errorNoSuchNick(message[1], fd);
    if (chanel.find(message[2]) != chanel.end())
    {
        if (!chanel[message[2]].hasClient(client.getNick()))
            return Utils::errorNotOnChannel(client.getNick(), message[2], fd);
        else if (chanel[message[2]].hasClient(message[1]))
            return Utils::errorUserOnChannel(client.getUser(), message[2], fd);
        else if (chanel[message[2]].getRootFd().find(client.getFd()) == chanel[message[2]].getRootFd().end())
            return Utils::errorChanOprivsNeed(client.getNick(), message[2], fd);
    }
    else    
        return Utils::errorNoSuchChannel(message[2], fd);
    std::string tmpMsg = ":localhost 341 " + client.getNick() + " " + message[1] + " " + message[2] + "\r\n";
    Utils::sendMessage(fd, tmpMsg);
    tmpMsg = ":localhost 301 " + client.getNick() + " " + message[1] + " :away_message\r\n";
    Utils::sendMessage(findClient(message[1], clients).getFd(), tmpMsg);
    chanel[message[2]].addInvite(findClient(message[1], clients).getFd(), findClient(message[1], clients).getNick());
}

bool InviteCommand::findNick(const std::string& nick, const std::map<int, Client>& clients)
{
    for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return true;
    }
    return false;
}

const Client& InviteCommand::findClient(const std::string nick, const std::map<int, Client>& clients)
{
    std::map<int, Client>::const_iterator it = clients.begin();
    for (; it != clients.end(); ++it)
    {
        if (it->second.getNick() == nick)
            return it->second;
    }
    throw std::runtime_error("");
}