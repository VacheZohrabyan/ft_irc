#include "../../inc/channel/partCommand.hpp"
#include "../../inc/channel/chanel.hpp"
#include "../../inc/client.hpp"

PartCommand::PartCommand()
{

}

PartCommand::~PartCommand()
{

}

void PartCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanel, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    if (chanel.find(message[1]) != chanel.end())
    {
        if (chanel[message[1]].hasClient(fd))
        {
            // :<nick>!<user>@<host> PART #channel :<reason>\r\n
            std::string temp;
            for (std::vector<std::string>::const_iterator it = message.begin() + 2; it != message.end(); ++it)
            {
                if (it != message.begin() + 2)
                    temp += " ";
                temp += *it;
            }
            std::string tmpMsg = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " PART " + message[1] + " " + temp + "\r\n";            
            chanel[message[1]].broadCast(tmpMsg, -1);
            chanel[message[1]].removeChanel(fd);
            if (chanel[message[1]].getCountClient() == 0)
                chanel.erase(message[1]);
        }
        else
            return Utils::errorNotOnChannel(message[1], fd);
    }
    else
        return Utils::errorNoSuchChannel(message[1], fd);
    (void)clients;
}