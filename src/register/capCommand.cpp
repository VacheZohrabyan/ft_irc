#include "../../inc/register/capCommand.hpp"
#include "../../inc/client.hpp"

CapCommand::CapCommand()
{

}

CapCommand::~CapCommand()
{

}

void CapCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    (void)client;
    (void)message;
    (void)_nickName;
    if (message[1] == "LS")
        Utils::sendMessage(fd, ":localhost CAP * LS\r\n");
    else if (message[1] == "END")
    {
        if (!client.getNick().empty() && !client.getUser().empty())
        {
            
            client.setIsRegistered(true);
            Utils::sendMessage(fd, ":localhost 001 " + client.getNick() + " :Welcome to IRC\r\n");
            Utils::sendMessage(fd, ":localhost 002 " + client.getNick() + " :Your host is localhost\r\n");
            Utils::sendMessage(fd, ":localhost 003 " + client.getNick() + " :This server was created today\r\n");
            Utils::sendMessage(fd, ":localhost 004 " + client.getNick() + " localhost 1.0 o o\r\n");
        }
    }
}