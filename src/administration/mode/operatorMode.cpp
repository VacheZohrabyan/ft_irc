#include "../../../inc/administration/mode/operatorMode.hpp"

OperatorMode::OperatorMode()
{

}

OperatorMode::~OperatorMode()
{

}

void OperatorMode::executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message)
{
    (void)chanels;
    (void)message;
    (void)client;
    (void)fd;
}