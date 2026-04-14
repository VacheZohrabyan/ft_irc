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
    (void)fd;
    (void)message;
    if (_nickName.find(client.getNick()) != _nickName.end())
        _nickName.erase(client.getNick());
}