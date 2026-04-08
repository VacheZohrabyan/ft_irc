#include "../../../inc/administration/mode/keyMode.hpp"

KeyMode::KeyMode()
{

}

KeyMode::~KeyMode()
{

}

void KeyMode::executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message)
{
    (void)chanels;
    (void)message;
    (void)client;
    (void)fd;
}