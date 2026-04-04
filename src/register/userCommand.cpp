#include "../../inc/register/userCommand.hpp"
#include "../../inc/client.hpp"

UserCommand::UserCommand()
{

}

UserCommand::~UserCommand()
{

}

void UserCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    (void)_nickName;
    if (client.getNick().empty())
        return Utils::errorMoreParams(client.getNick(), fd);
    if (_nickName.find(message[1]) != _nickName.end() && !client.getIsRegistered())
    {
        Utils::errorNickNameInUse(message[1], fd);
        return ;
    }
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
}