#include "../../inc/channel/topicCommand.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"

TopicCommand::TopicCommand()
{

}

TopicCommand::~TopicCommand()
{

}

void TopicCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    (void)clients;
    if (message.size() == 2)
    {
        if (chanel.find(message[1]) == chanel.end())
            return Utils::errorNoSuchChannel(message[1], fd);
        std::string tmpMsg;
        if (chanel[message[1]].getTopic().empty())
            tmpMsg = ":localhost 331 " + client.getNick() + " " + message[1] + " :No topic is set\r\n";
        else
            tmpMsg = ":localhost 332 " + client.getNick() + " " + message[1] + " " + chanel[message[1]].getTopic() + "\r\n";
        Utils::sendMessage(fd, tmpMsg);
        return ;
    }
    if (message.size() < 3)
        return Utils::errorMoreParams(client.getNick(), fd);
    if (chanel.find(message[1]) == chanel.end())
        return Utils::errorNoSuchChannel(message[1], fd);
    if (chanel[message[1]].getChanelClients().find(fd) == chanel[message[1]].getChanelClients().end())
        return Utils::errorNotOnChannel(message[1], fd);
    if (chanel[message[1]].getTopicProtection() && chanel[message[1]].getRootFd().find(fd) == chanel[message[1]].getRootFd().end())
        return Utils::errorChanOprivsNeed(client.getNick(), message[1], fd);
    chanel[message[1]].setTopic(message[2].substr(1, message[2].length()));
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + "localhost TOPIC " + message[1] + " " + concatMessage(message) + "\r\n";
    chanel[message[1]].broadCast(tmpMsg, -1);
}

std::string TopicCommand::concatMessage(const std::vector<std::string>& message) const
{
    std::string tmpMsg;

    for (std::vector<std::string>::const_iterator it = message.begin() + 2; it != message.end(); ++it)
    {
        if (it != message.begin() + 2)
            tmpMsg += " ";
        tmpMsg += *it;
    }
    return tmpMsg;
}