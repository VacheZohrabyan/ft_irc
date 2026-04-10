#include "../../../inc/administration/mode/limitMode.hpp"
#include "../../../inc/channel/chanel.hpp"
#include "../../../inc/client.hpp"

LimitMode::LimitMode()
{

}

LimitMode::~LimitMode()
{

}

void LimitMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& message, bool flag)
{
    std::cout << chanel.getRootFd() << " " << fd << std::endl;
    if (chanel.getRootFd() != fd)
        return Utils::errorErroneUsNickName(client.getNick(), fd);
    for (std::string::size_type i = 0; i < message.length(); ++i)
    {
        if (!std::isdigit(message[i]) && message[i] != '-')
            return ;
    }
    if (!chanel.getLimit())
    {
        if (flag)
            addLimit(client, chanel, message, flag);
        else
            subLimit(client, chanel, flag);
    }
    else
    {
        if (!flag)
            subLimit(client, chanel, flag);
        else
            addLimit(client, chanel, message, flag);
    }
}

void LimitMode::addLimit(Client& client, Chanel& chanel, const std::string& message, bool flag) const
{
    chanel.setLimit(flag);
    std::size_t count = std::stoul(message);
    chanel.setMaxCount(count);
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " +l " + std::to_string(chanel.getMaxCount()) + "\r\n";
    chanel.broadCast(tmpMsg, -1);
    std::cout << "tmpMsg = " << tmpMsg;
}

void LimitMode::subLimit(Client& client, Chanel& chanel, bool flag) const
{
    chanel.setLimit(flag);
    chanel.setMaxCount(std::numeric_limits<std::size_t>::max());
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " -l " + std::to_string(chanel.getMaxCount()) + "\r\n";
    chanel.broadCast(tmpMsg, -1);
}