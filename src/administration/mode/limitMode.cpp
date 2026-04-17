#include "../../../inc/administration/mode/limitMode.hpp"
#include "../../../inc/channel/chanel.hpp"
#include "../../../inc/client.hpp"

LimitMode::LimitMode()
{

}

LimitMode::~LimitMode()
{

}

void LimitMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients)
{
    if (chanel.getRootFd().find(fd) == chanel.getRootFd().end())
        return Utils::errorErroneUsNickName(client.getNick(), fd);
    for (std::string::size_type i = 0; i < message.length(); ++i)
        if (!std::isdigit(message[i]) && message[i] != '-')
            return ;
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
    (void)clients;
}

void LimitMode::addLimit(Client& client, Chanel& chanel, const std::string& message, bool flag) const
{
    chanel.setLimit(flag);
    std::size_t count = std::atoll(message.c_str());
    chanel.setMaxCount(count);
    std::stringstream ss;
    ss << chanel.getMaxCount();
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " +l " + ss.str() + "\r\n";
    chanel.broadCast(tmpMsg, -1);
}

void LimitMode::subLimit(Client& client, Chanel& chanel, bool flag) const
{
    chanel.setLimit(flag);
    chanel.setMaxCount(std::numeric_limits<std::size_t>::max());
    std::stringstream ss;
    ss << chanel.getMaxCount();
    std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanel.getChanelName() + " -l " + ss.str() + "\r\n";
    chanel.broadCast(tmpMsg, -1);
}