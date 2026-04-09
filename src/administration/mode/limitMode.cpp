#include "../../../inc/administration/mode/limitMode.hpp"
#include "../../../inc/channel/chanel.hpp"
#include "../../../inc/client.hpp"

LimitMode::LimitMode()
{

}

LimitMode::~LimitMode()
{

}

void LimitMode::executeMode(Client& client, Chanel& chanel, int fd, const std::string& chanelName, const std::string& message, bool flag)
{
    if (chanel.getRootFd() != fd)
        return Utils::errorErroneUsNickName(client.getNick(), fd);
    if (!chanel.getLimit())
    {
        // :nick!user@host MODE #test +l 10
        if (flag)
        {
            chanel.setLimit(flag);
            std::size_t count = std::stoul(message);
            chanel.setMaxCount(count);
            std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanelName + "+l " + message + "\r\n";
            chanel.broadCast(tmpMsg, -1);
        }
    }
    else
    {
        // :nick!user@host MODE #test -l 10
        if (!flag)
        {
            chanel.setLimit(flag);
            chanel.setMaxCount(std::numeric_limits<std::size_t>::max());
            std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " MODE " + chanelName + "-l " + message + "\r\n";
            chanel.broadCast(tmpMsg, -1);
        }
    }
}