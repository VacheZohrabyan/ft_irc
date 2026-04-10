#include "../../../inc/administration/mode/keyMode.hpp"
#include "../../../inc/channel/chanel.hpp"
#include "../../../inc/client.hpp"

KeyMode::KeyMode()
{

}

KeyMode::~KeyMode()
{

}

void KeyMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients)
{
    if (chanel.getRootFd().find(fd) == chanel.getRootFd().end())
        return Utils::errorChanOprivsNeed(client.getNick(), chanel.getChanelName(), fd);
    if (!chanel.getChanelPasswd())
    {
        if (flag)
            addKey(client, chanel, flag, message);
        else
            subKey(client, chanel, flag);
    }
    else
    {
        if (!flag)
            subKey(client, chanel, flag);
        else
            addKey(client, chanel, flag, message);
    }
    (void)clients;
}

void KeyMode::addKey(Client& client, Chanel& chanel, bool flag, const std::string& message) const
{
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " +k " + message + "\r\n";
    chanel.broadCast(tmpMsg, -1);
    chanel.setChanelPasswd(flag);
    chanel.setChanelKey(message);
}

void KeyMode::subKey(Client& client, Chanel& chanel, bool flag) const
{
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " -k\r\n";
    chanel.broadCast(tmpMsg, -1);
    chanel.setChanelPasswd(flag);
}