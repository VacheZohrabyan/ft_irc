#include "../../inc/register/userCommand.hpp"
#include "../../inc/client.hpp"

UserCommand::UserCommand()
{

}

UserCommand::~UserCommand()
{

}

void UserCommand::executeCommand(Client& client, int fd, std::vector<std::string>& message)
{
    if (client.getNick().empty())
        Utils::errorMoreParams(client.getNick(), fd);
    if (message.size() < 5)
        Utils::errorMoreParams(client.getNick(), fd);
    for (std::vector<std::string>::const_iterator it = message.begin() + 1; it != message.end(); ++it)
    {
        if ((*it).empty())
            Utils::errorMoreParams(client.getNick(), fd);
    }
    client.setUser(message[1]);
    client.setHost(message[2]);
    client.setServer(message[3]);
    client.setReal(message[4].substr(1, message[4].length()) + (message.size() == 5 ? "" : (" " + message[5])));
    std::cout << "stex1" << std::endl;
}