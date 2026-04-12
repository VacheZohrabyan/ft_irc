#include "../../inc/register/pingCommand.hpp"
#include "../../inc/client.hpp"
PingCommand::PingCommand()
{

}

PingCommand::~PingCommand()
{

}

void PingCommand::executeCommand(Client& client, std::set<std::string>& nickName, int fd, std::vector<std::string>& message)
{
    (void)nickName;
    (void)message;
    (void)fd;
    std::string tmpMsg = "PONG " + message[1] + "\r\n";
    Utils::sendMessage(client.getFd(), tmpMsg);
}