#include "../../inc/message/noticeCommand.hpp"

NoticeCommand::NoticeCommand()
{

}

NoticeCommand::~NoticeCommand()
{

}

void NoticeCommand::executeCommand(Client& client, const std::map<int, Client>& clients, Chanel& chanel, int fd, std::vector<std::string>& message)
{
    (void)client;
    (void)chanel;
    (void)fd;
    (void)message;
    (void)clients;
}