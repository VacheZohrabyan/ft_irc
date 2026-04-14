#include "../../inc/administration/operCommand.hpp"

OperCommand::OperCommand()
{
    // _mode["KILL"] = new KillCommand();
    // _mode["REHASH"] = new RehashCommand();
    // _mode["RESTART"] = new RestartCommand();
    // _mode["SQUIT"] = new SQuitCommand();
    // _mode["WALLOPS"] = new WallopsCommand();
    // _mode["DIE"] = new DieCommand();
    // _mode["CONNECT"] = new ConnectCommand();
    // _mode["STATS"] = new StatsCommand();
}

OperCommand::~OperCommand()
{

}

void OperCommand::executeCommand(Client& client, std::map<std::string, Chanel>& chanels, int fd, std::vector<std::string>& message, const std::map<int, Client>& clients)
{
    (void)client;
    (void)clients;
    (void)chanels;
    (void)message;
    (void)fd;
}
