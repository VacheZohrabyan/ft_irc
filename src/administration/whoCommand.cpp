#include "../../inc/administration/whoCommand.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"

WhoCommand::WhoCommand()
{

}

WhoCommand::~WhoCommand()
{

}

void WhoCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    // :localhost 352 vzohraby #test user host server vzohraby_ H@ :0 Real Name
    if (chanels.find(message[1]) == chanels.end())
        return ;
    for (std::map<int, std::string>::const_iterator it = chanels[message[1]].getChanelClients().begin(); it != chanels[message[1]].getChanelClients().end(); ++it)
    {
        std::map<int, Client>::const_iterator itClient = clients.find(it->first);
        std::string tmpMsg = ":localhost 352 " + client.getNick() + " " + message[1] + " " + itClient->second.getUser() + " " 
        + itClient->second.getHost() + " " + itClient->second.getServer() + " localhost " 
        +  itClient->second.getNick() + " H@ :0 " + itClient->second.getReal() + "\r\n";
        Utils::sendMessage(fd, tmpMsg);
    }
    // :localhost 315 vzohraby #test :End of /WHO list
    std::string tmpMsg = ":localhost 315 " + client.getNick() + " " + message[1] + " :End of /WHO list\r\n";
    Utils::sendMessage(fd, tmpMsg);
}