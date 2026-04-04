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
    if ((client.getPass().empty() && !client.getServerPass().empty()) || (!client.getPass().empty() && client.getServerPass().empty()))
        Utils::errorMoreParams(client.getNick(), fd);
    if (message[1].empty() || message.size() < 2)
        Utils::errorMoreParams(client.getNick(), fd);
    // if (_nickName.find(message[1]) != _nickName.end())
    // {
    //     std::cout << "stex = " << message[1] << std::endl;
    //     Utils::errorNickNameInUse(message[1], fd);
    //     return ;
    // }
    if (!client.getNick().empty())
        _nickName.erase(client.getNick());
    client.setNick(message[1]);
    _nickName.insert(client.getNick());
}