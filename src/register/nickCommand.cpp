#include "../../inc/register/nickCommand.hpp"
#include "../../inc/client.hpp"

NickCommand::NickCommand()
{

}

NickCommand::~NickCommand()
{

}

bool NickCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    (void)_nickName;
    
    if (message.size() < 2 || message[1].empty())
        return (Utils::errorMoreParams(client.getNick(), fd), false);
    if (!client.getNick().empty())
    {
        if (_nickName.find(message[1]) != _nickName.end())
            return (Utils::errorNickNameInUse(message[1], fd), false);
        else
            _nickName.erase(client.getNick());
        client.setNick(message[1]);
        _nickName.insert(client.getNick());
    }
    else
    {
        if (_nickName.find(message[1]) != _nickName.end())
            return (Utils::errorNickNameInUse(message[1], fd), false);
        else
        {
            client.setNick(message[1]);
            _nickName.insert(client.getNick());
        }
    }
    return true;
}