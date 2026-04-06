#include "../../inc/register/quitCommand.hpp"
#include "../../inc/client.hpp"

QuitRegisterCommand::QuitRegisterCommand()
{

}

QuitRegisterCommand::~QuitRegisterCommand()
{

}

void QuitRegisterCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    // _nickName.erase(client.getNick());
    (void)client;
    (void)_nickName;
    (void)fd;
    (void)message;
    // _nickName.erase(client.getNick());
}