#include "../../../inc/administration/mode/keyMode.hpp"
#include "../../../inc/channel/chanel.hpp"

KeyMode::KeyMode()
{

}

KeyMode::~KeyMode()
{

}

void KeyMode::executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag)
{
    (void)chanels;
    (void)flag;
    (void)message;
    (void)client;
    (void)fd;
    std::cout << "stex2\n";
    chanels.setChanelPasswd(true);
}