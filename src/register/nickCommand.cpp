#include "../../inc/register/nickCommand.hpp"
#include "../../inc/client.hpp"

NickCommand::NickCommand()
{

}

NickCommand::~NickCommand()
{

}

void NickCommand::executeCommand(Client& client, std::set<std::string>& _nickName, int fd, std::vector<std::string>& message)
{
    (void)_nickName;
    
    if (message[1].empty() || message.size() < 2)
        Utils::errorMoreParams(client.getNick(), fd);
    if (!client.getNick().empty())
    {
        if (_nickName.find(message[1]) != _nickName.end())
            Utils::errorNickNameInUse(message[1], fd);
        else
            _nickName.erase(client.getNick());
        client.setNick(message[1]);
        _nickName.insert(client.getNick());
    }
    else
    {
        if (_nickName.find(message[1]) != _nickName.end())
            return Utils::errorNickNameInUse(message[1], fd);
        else
        {
            client.setNick(message[1]);
            _nickName.insert(client.getNick());
        }
    }
}