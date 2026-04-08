#include "../../inc/administration/modeCommand.hpp"

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

void ModeCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message)
{
    // bool _adding = false;
    std::vector<std::string>::size_type index = 3;
    for (std::string::size_type i = 1; i < message[2].length(); ++i)
    {
        if (_modeCommand.find(message[2][i]) != _modeCommand.end())
            _modeCommand[message[2][i]]->executeMode(client, chanels, fd, (message.size() <= index) ? "" : message[index++]);
        else
        {
            std::string tmpMsg;
            tmpMsg += message[2][i];
            Utils::errorUnknownMode(tmpMsg, fd);
        }
    }
}