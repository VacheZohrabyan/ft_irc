#include "../../inc/channel/joinCommand.hpp"
#include "../../inc/client.hpp"

JoinCommand::JoinCommand()
{

}

JoinCommand::~JoinCommand()
{

}

void JoinCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message)
{
    std::cout << "stex1\n";
    if (message.size() < 2)
        Utils::errorMoreParams(client.getNick(), fd);
    std::cout << "stex2\n";
    if (message[1].empty() || (message[1][0] != '#' && message[1][0] != '&'))
        Utils::errorBadChanMask(client.getNick(), fd);
    std::cout << "stex3\n";
    if (chanel.find(message[1]) == chanel.end() && chanel.size() == MAX_CHANELL)
        Utils::errorNoSuchChannel(client.getNick(), fd);
    std::cout << "stex4\n";
    if (chanel.size() == MAX_CHANELL)
        Utils::errorTooManyChannels(message[1], fd);
    std::cout << "stex5\n";
    if (chanel[message[1]].getCountClient() == MAX_CLIENT)
        Utils::errorChannelIsFull(message[1], fd);
    std::cout << "stex6\n";
    if (chanel.find(message[1]) == chanel.end())
        chanel[message[1]] = Chanel(message[1], fd, (message.size() == 3 && !message[3].empty()) ? message[3] : "");
    else
        chanel[message[1]].addClient(fd, client.getNick());
    std::cout << "stex7\n";
    std::string joinMessage = ":" + client.getNick() + "!" + client.getUser() + " " + message[0] + " :" + message[1] + "\r\n";
    chanel[message[1]].broadCast(joinMessage, -1);
    joinMessage = ":localhost 332 " + client.getNick() + " " + message[1] + (chanel[message[1]].getTopic().empty() ? " :No topic is set" : chanel[message[1]].getTopic()) + "\r\n";
    Utils::sendMessage(fd, joinMessage);
    chanel[message[1]].showAll(fd);
    joinMessage = ":localhost 366 " + client.getNick() + message[1] + " :End of /NAMES list\r\n";
    Utils::sendMessage(fd, joinMessage);
    
    // :<nick>!<user>@<host> JOIN :<channel> //iran
    // :localhost 332 <nick> <channel> :<topic_text> //chanel
}