#include "../../inc/channel/kickCommand.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/quitCommand.hpp"

KickCommand::KickCommand()
{

}

KickCommand::~KickCommand()
{

}

void KickCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    if (chanel.find(message[1]) == chanel.end())
        return Utils::errorNoSuchChannel(message[1], fd);
    if (!chanel[message[1]].hasClient(client.getNick()))
        return Utils::errorNotOnChannel(message[1], fd);
    if (chanel[message[1]].getRootFd().find(client.getFd()) == chanel[message[1]].getRootFd().end())
        return Utils::errorChanOprivsNeed(client.getNick(), message[1], fd);
    if (!chanel[message[1]].hasClient(message[2]))
        return Utils::errorUserNotInChannel(message[2], message[1], fd);
    // :[Sender_Nick]![User]@[Host] KICK [Channel_Name] [Target_Nick] :[Reason]
    std::string tmp = concatMessage(message); 
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " KICK " + message[1] + " " + message[2] + " " + (tmp.size() == 1 ? (":" + message[2]) : tmp) + "\r\n";
    chanel[message[1]].broadCast(tmpMsg, -1);
    chanel[message[1]].removeClient(findClient(message[2], clients));
    if (chanel[message[1]].getCountClient() == 0)
        chanel.erase(message[1]);
}

std::string KickCommand::concatMessage(const std::vector<std::string>& message) const
{
    std::string tmp;
    for (std::vector<std::string>::const_iterator it = message.begin() + 3; it != message.end(); ++it)
    {
        if (it != message.begin() + 3)
            tmp += " ";
        tmp += *it;
    }
    return tmp;
}

int KickCommand::findClient(const std::string& nick, const std::map<int, Client>& clients) const
{
    for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
        if (it->second.getNick() == nick)
            return it->first;
    throw std::runtime_error("");
}