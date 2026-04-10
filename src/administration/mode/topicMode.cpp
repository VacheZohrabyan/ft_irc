#include "../../../inc/administration/mode/topicMode.hpp"

TopicMode::TopicMode()
{

}

TopicMode::~TopicMode()
{

}

void TopicMode::executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag)
{
    (void)chanels;
    (void)message;
    (void)client;
    (void)fd;
    (void)flag;
}