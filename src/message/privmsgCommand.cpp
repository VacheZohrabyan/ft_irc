#include "../../inc/message/privmsgCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/chanel.hpp"

PrivMsgCommand::PrivMsgCommand()
{

}

PrivMsgCommand::~PrivMsgCommand()
{

}

void PrivMsgCommand::executeCommand(Client& client, const std::map<int, Client>& clients, Chanel& chanel, int fd, std::vector<std::string>& message)
{
    if (message.size() != 3)
        Utils::errorNoSuchNick(message[1], fd);
    if (message[2].empty())
        Utils::errorNoTestToSend(fd);

    std::cout << "message0 = " << message[0];
    std::cout << "message1 = " << message[1];
    std::cout << "message2 = " << message[2];
    if (message[1][0] == '&' || message[1][0] == '#')
    {
        std::string temp;
        for (std::vector<std::string>::const_iterator it = message.begin() + 2; it != message.end(); ++it)
        {
            temp += *it;
            temp += " ";
        }
        std::string tmp = ":" + client.getNick() + "!" + client.getUser() + "@" + client.getHost() + " PRIVMSG " + message[1] + " " + temp + "\r\n";
        std::cout << "tmp = " << tmp;
        chanel.broadCast(tmp, fd);
    }
    else
    {
        for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if (it->second.getNick() == message[1])
            {
                std::string temp;
                for (std::vector<std::string>::const_iterator it = message.begin() + 2; it != message.end(); ++it)
                {
                    if (it != message.begin())
                        temp += " ";
                    temp += *it;
                }
                std::string tmp = ":" + client.getNick() + "!" + client.getUser() + "@" + it->second.getNick() + " PRIVMSG " + temp + "\r\n";
                Utils::sendMessage(it->first, tmp);
                return;
            }
        }
    }

    (void)client;
    (void)chanel;
    (void)fd;
    (void)message;
}