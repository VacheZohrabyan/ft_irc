#include "../../../inc/administration/mode/limitMode.hpp"

LimitMode::LimitMode()
{

}

LimitMode::~LimitMode()
{

}

void LimitMode::executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message)
{
    (void)chanels;
    (void)message;
    (void)client;
    (void)fd;
}