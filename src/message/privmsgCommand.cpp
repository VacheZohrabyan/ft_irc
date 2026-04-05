#include "../../inc/message/privmsgCommand.hpp"

PrivMsgCommand::PrivMsgCommand()
{

}

PrivMsgCommand::~PrivMsgCommand()
{

}

void PrivMsgCommand::executeCommand(Client& client, Chanel& chanel, int fd, std::vector<std::string>& message)
{
    (void)client;
    (void)chanel;
    (void)fd;
    (void)message;
}