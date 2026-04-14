#include "../../inc/channel/quitCommand.hpp"
#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"

QuitChannelCommand::QuitChannelCommand()
{

}

QuitChannelCommand::~QuitChannelCommand()
{

}

void QuitChannelCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    for (std::map<std::string, Chanel>::iterator it = chanel.begin(); it != chanel.end(); ++it)
    {
        if (it->second.hasClient(fd))
        {
            std::string temp;
            for (std::vector<std::string>::const_iterator it = message.begin() + 1; it != message.end(); ++it)
            {
                if (it != message.begin() + 1)
                    temp += " ";
                temp += *it;
            }
            std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@localhost QUIT " + temp + "\r\n"; 
            it->second.broadCast(tmpMsg, fd);
            it->second.removeChanel(fd);
            if (it != chanel.end() && it->second.getCountClient() == 0)
                chanel.erase(it->first);
        }
    }
    (void)clients;
}