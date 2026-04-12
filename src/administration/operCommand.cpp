#include "../../inc/administration/operCommand.hpp"

OperCommand::OperCommand()
{
    _mode["KILL"]
    _mode["REHASH"]
    _mode["RESTART"]
    _mode["SQUIT"]
    _mode["WALLOPS"]
    _mode["DIE"]
    _mode["CONNECT"]
    _mode["STATS"]
}

OperCommand::~OperCommand()
{

}

void OperCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    std::map<int, Client>& clientss = const_cast<std::map<int, Client>&>(clients);

}
