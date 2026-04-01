#include "../../inc/register/pingCommand.hpp"

PingCommand::PingCommand()
{

}

PingCommand::~PingCommand()
{

}

void PingCommand::executeCommand(Client& client, int fd, std::vector<std::string>& message)
{
    (void)client;
    Utils::sendMessage(fd, "PONG : " + message[1] + "\r\n");
}