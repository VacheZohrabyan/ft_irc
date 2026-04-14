#include "../../inc/message/quitCommand.hpp"
#include "../../inc/client.hpp"

QuitMessageCommand::QuitMessageCommand()
{

}

QuitMessageCommand::~QuitMessageCommand()
{

}

void QuitMessageCommand::executeCommand(Client& client, std::map<int, Client>& clients, Chanel& chanel, int fd, std::vector<std::string>& message)
{
    (void)client;
    (void)clients;
    (void)chanel;
    (void)message;
    (void)fd;
}