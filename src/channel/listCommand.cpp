#include "../../inc/channel/listCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/chanel.hpp"

ListCommand::ListCommand()
{

}

ListCommand::~ListCommand()
{

}

void ListCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message)
{
    // :localhost 321 <nick> Channel :Users  Name
    std::string plainText = ":localhost 321 " + client.getNick() + " Channel :Users  Name" + "\r\n";
    Utils::sendMessage(fd, plainText);
    if (message.size() == 2)
    {
        std::vector<std::string> tmp = Utils::mySplit(message[1], ',');
        // :<server> 322 <client_nick> <channel_name> <num_users> :<topic>                
        for (std::vector<std::string>::const_iterator i = tmp.begin(); i != tmp.end(); ++i)
            if (chanel.find(*i) != chanel.end())
                helperFunction(chanel[*i].getCountClient(), fd, client.getNick(), *i, chanel[*i].getTopic());
    }
    else
    {
        // :localhost 322 vzohraby #test 3 :Welcome to our channel!
        for (std::map<std::string, Chanel>::const_iterator it_ch = chanel.begin(); it_ch != chanel.end(); ++it_ch)
            helperFunction(it_ch->second.getCountClient(), fd, client.getNick(), it_ch->first, it_ch->second.getTopic());
    }
    // :localhost 323 <nick> :End of /LIST
    std::string endOfList = ":localhost 323 " + client.getNick() + " :End of /LIST\r\n";
}

void ListCommand::helperFunction(int count, int fd, const std::string& clientNick, const std::string& chanelName, const std::string& topic) const
{
    std::stringstream ss;
    ss << count;
    std::string chanelNameAndUser = ":localhost 322 " + clientNick + " " + chanelName + " " + ss.str() + " :" + (!topic.empty() ? topic : "No topic is set") + "\r\n";
    Utils::sendMessage(fd, chanelNameAndUser);
}