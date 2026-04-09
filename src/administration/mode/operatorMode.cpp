#include "../../../inc/administration/mode/operatorMode.hpp"

OperatorMode::OperatorMode()
{

}

OperatorMode::~OperatorMode()
{

}

void OperatorMode::executeMode(Client& client, Chanel& chanels, int fd, const std::string& chanelName, const std::string& message, bool flag)
{
    (void)chanels;
    (void)flag;
    (void)message;
    (void)chanelName;
    (void)client;
    (void)fd;
}