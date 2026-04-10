#include "../../inc/channel/joinCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/namesCommand.hpp"

JoinCommand::JoinCommand()
{

}

JoinCommand::~JoinCommand()
{

}

void JoinCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message)
{
    std::cout << "JOin fd = " << fd << std::endl;
    if (message.size() < 2)
        Utils::errorMoreParams(client.getNick(), fd);
    if (message[1].empty() || (message[1][0] != '#' && message[1][0] != '&'))
        Utils::errorBadChanMask(client.getNick(), fd);
    std::map<std::string, Chanel>::iterator it = chanel.find(message[1]);
    if (it == chanel.end())
    {
        if (chanel.size() == MAX_CHANELL)
            return Utils::errorNoSuchChannel(client.getNick(), fd);
        Chanel newChanel(message[1], fd, (message.size() == 3 && !message[2].empty()) ? message[2] : "");
        newChanel.addClient(fd, client.getNick());
        chanel.insert(std::make_pair(message[1], newChanel));
    }
    else
    {
        if (it->second.getLimit())
            if (it->second.getCountClient() == it->second.getMaxCount())
                Utils::errorChannelIsFull(message[1], fd);
        if (chanel[message[1]].getChanelPasswd() && chanel[message[1]].getChannelPass() != ((message.size() == 3 && !message[2].empty()) ? message[2] : ""))
            return Utils::errorBadChannelKey(client.getNick(), fd);
        it->second.addClient(fd, client.getNick());
    }
    std::string joinMessage = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " " + message[0] + " :" + message[1] + "\r\n";
    chanel[message[1]].broadCast(joinMessage, -1);
    joinMessage = ":localhost 332 " + client.getNick() + " " + message[1] + " :" + (chanel[message[1]].getTopic().empty() ? "No topic is set" : chanel[message[1]].getTopic()) + "\r\n";
    Utils::sendMessage(fd, joinMessage);
    NamesCommand().executeCommand(client, chanel, fd, message);
}