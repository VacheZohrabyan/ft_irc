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
        return ;
}