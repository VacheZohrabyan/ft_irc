#include "../../../inc/administration/mode/operatorMode.hpp"
#include "../../../inc/client.hpp"
#include "../../../inc/channel/chanel.hpp"

OperatorMode::OperatorMode()
{

}

OperatorMode::~OperatorMode()
{

}

void OperatorMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients)
{
    if (chanel.getRootFd().find(fd) == chanel.getRootFd().end())
        return Utils::errorChanOprivsNeed(client.getNick(), chanel.getChanelName(), fd);
    if (!findNick(clients, message))
        return Utils::errorNoSuchNick(client.getNick(), message, fd);
    if (!chanel.hasClient(message))
        return Utils::errorUserNotInChannel(client.getNick(), message, fd);
    if (flag)
    {
        chanel.setOperatorPrivilege(getFd(clients, message));
        std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " +o " + message + "\r\n";
        chanel.broadCast(tmpMsg, -1);
    }
    else
    {
        chanel.removeRootFd(getFd(clients,message));
        std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " -o " + message + "\r\n";
        chanel.broadCast(tmpMsg, -1);
    }
}

bool OperatorMode::findNick(const std::map<int, Client>& clients, const std::string& message) const
{
    for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
        if (it->second.getNick() == message)
            return true;
    return false;
}

int OperatorMode::getFd(const std::map<int, Client>& clients, const std::string& message) const
{
    for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
        if (it->second.getNick() == message)
            return it->first;
    return -1;
}