#include "../../inc/register/pingCommand.hpp"

PingCommand::PingCommand()
{

}

PingCommand::~PingCommand()
{

}

void PingCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    (void)client;
    (void)_nickName;
    Utils::sendMessage(fd, "PONG : " + message[1] + "\r\n");
}