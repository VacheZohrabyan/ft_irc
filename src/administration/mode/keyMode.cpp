#include "../../../inc/administration/mode/keyMode.hpp"

KeyMode::KeyMode()
{

}

KeyMode::~KeyMode()
{

}

void KeyMode::executeMode(Client& client, Chanel& chanels, int fd, const std::string& chanelName, const std::string& message, bool flag)
{
    (void)chanels;
    (void)flag;
    (void)message;
    (void)client;
    (void)chanelName;
    (void)fd;
}