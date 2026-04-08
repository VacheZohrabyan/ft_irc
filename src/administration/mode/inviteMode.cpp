#include "../../../inc/administration/mode/inviteMode.hpp"

InviteMode::InviteMode()
{

}

InviteMode::~InviteMode()
{

}

void InviteMode::executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message)
{
    (void)chanels;
    (void)message;
    (void)client;
    (void)fd;
}