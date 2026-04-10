#include "../../inc/administration/modeCommand.hpp"
#include "../../inc/client.hpp"
#include "../../inc/channel/chanel.hpp"

ModeCommand::ModeCommand()
{
    _modeCommand['i'] = new InviteMode();
    _modeCommand['t'] = new TopicMode();
    _modeCommand['k'] = new KeyMode();
    _modeCommand['l'] = new LimitMode();
    _modeCommand['o'] = new OperatorMode();
}

ModeCommand::~ModeCommand()
{
    for (std::map<char, AModeCommand*>::iterator it = _modeCommand.begin(); it != _modeCommand.end(); ++it)
        delete it->second;
    _modeCommand.clear();
}

void ModeCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    if (message.size() == 2)
    {
        if (chanels.find(message[1]) != chanels.end())
        {
            // <client> <channel> <modestring> <mode_params>
            std::string tmpMsg = ":localhost 324 " + client.getNick() + " " + message[1] + " +";
            std::string numMsg;
            if (chanels[message[1]].getInviteOnly())
                tmpMsg += "i";
            if (chanels[message[1]].getChanelPasswd())
            {
                tmpMsg += "k";
                numMsg += " " + chanels[message[1]].getChannelPass();
            }
            if (chanels[message[1]].getChanelPasswd())
                tmpMsg += "p"; 
            if (chanels[message[1]].getLimit())
            {
                std::stringstream ss;
                ss << chanels[message[1]].getMaxCount();
                tmpMsg += "l";
                numMsg += " " + ss.str();
            }
            tmpMsg += numMsg + "\r\n";
            Utils::sendMessage(fd, tmpMsg);
            tmpMsg = ":localhost 329 " + client.getNick() + " " + message[1] + " " + std::to_string(chanels[message[1]].getTime()) + "\r\n";
            Utils::sendMessage(fd, tmpMsg);
        }
        else
            Utils::errorNoSuchChannel(message[1], fd);
    }
    else
    {
        if (chanels.find(message[1]) == chanels.end())
            return ;
        std::vector<std::string>::size_type index = 3;
        std::string::size_type i = 0;

        for (; index <= message.size() && i < message.size(); i++)
        {
            if (message[2][i] == '+')
            {
                _adding = true;
                continue;
            }
            if (message[2][i] == '-')
            {
                std::cout << "stex2\n";
                _adding = false;
                continue;
            }
            if (_modeCommand.find(message[2][i]) != _modeCommand.end())
                _modeCommand[message[2][i]]->executeMode(client, chanels[message[1]], fd, (message[index].empty() ? "" : message[index++]), _adding, clients);
        }  
    }
}
