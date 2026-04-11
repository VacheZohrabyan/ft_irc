#include "../../inc/channel/namesCommand.hpp"
#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"

NamesCommand::NamesCommand()
{

}

NamesCommand::~NamesCommand()
{

}

void NamesCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    if (chanel.find(message[1]) != chanel.end())
    {
        chanel[message[1]].showAll(fd, client);
        std::string joinMessage = ":localhost 366 " + client.getNick() + " " + message[1] + " :End of /NAMES list\r\n";
        Utils::sendMessage(fd, joinMessage);
    }
    (void)clients;
}
