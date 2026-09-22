#include "../../inc/register/capCommand.hpp"
#include "../../inc/client.hpp"

CapCommand::CapCommand()
{

}

CapCommand::~CapCommand()
{

}

bool CapCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    (void)client;
    (void)_nickName;
    if (message[1] == "LS")
        return (Utils::sendMessage(fd, ":localhost CAP * LS\r\n"), true);
    else if (message[1] == "END")
        return true;
    return true;
}