#include "../../inc/register/nickCommand.hpp"
#include "../../inc/client.hpp"

NickCommand::NickCommand()
{

}

NickCommand::~NickCommand()
{

}

void NickCommand::executeCommand(Client& client, int fd, std::vector<std::string>& message)
{
    if ((client.getPass().empty() && !client.getServerPass().empty()) || (!client.getPass().empty() && client.getServerPass().empty()))
        Utils::errorMoreParams(client.getNick(), fd);
    if (message[1].empty() || message.size() > 2)
        Utils::errorMoreParams(client.getNick(), fd);
    client.setNick(message[1]);
    std::cout << "stex3" << std::endl;
}