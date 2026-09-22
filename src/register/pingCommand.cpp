#include "../../inc/register/pingCommand.hpp"
#include "../../inc/client.hpp"
PingCommand::PingCommand()
{

}

PingCommand::~PingCommand()
{

}

bool PingCommand::executeCommand(Client& client, std::set<std::string>& nickName, int fd, std::vector<std::string>& message)
{
    (void)nickName;
    (void)message;
    (void)fd;
    std::string tmpMsg = "PONG " + message[1] + "\r\n";
    return (Utils::sendMessage(client.getFd(), tmpMsg), true);
}