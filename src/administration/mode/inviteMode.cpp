#include "../../../inc/administration/mode/inviteMode.hpp"
#include "../../../inc/channel/chanel.hpp"
#include "../../../inc/client.hpp"

InviteMode::InviteMode()
{

}

InviteMode::~InviteMode()
{

}

void InviteMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients)
{
    if (chanel.getRootFd().find(fd) == chanel.getRootFd().end())
        return Utils::errorChanOprivsNeed(client.getNick(), chanel.getChanelName(), fd);
    if (flag)
    {
        chanel.setInviteOnly(flag);
        std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " +i\r\n";
        chanel.broadCast(tmpMsg, -1); 
    }
    else
    {
        chanel.setInviteOnly(flag);
        std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " -i\r\n";
        chanel.broadCast(tmpMsg, -1); 
    }
    (void)clients;
    (void)message;
}