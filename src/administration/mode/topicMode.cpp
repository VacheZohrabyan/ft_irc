#include "../../../inc/administration/mode/topicMode.hpp"
#include "../../../inc/channel/chanel.hpp"
#include "../../../inc/client.hpp"

TopicMode::TopicMode()
{

}

TopicMode::~TopicMode()
{

}

void TopicMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients)
{
    if (chanel.getRootFd().find(fd) == chanel.getRootFd().end())
        return Utils::errorChanOprivsNeed(client.getNick(), chanel.getChanelName(), fd);
    if (flag)
    {
        chanel.setTopicProtection(flag);
        std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " +t\r\n";
        chanel.broadCast(tmpMsg, -1); 
    }
    else
    {
        chanel.setTopicProtection(flag);
        std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " -t\r\n";
        chanel.broadCast(tmpMsg, -1); 
    }
    (void)chanel;
    (void)message;
    (void)client;
    (void)fd;
    (void)flag;
    (void)clients;
}