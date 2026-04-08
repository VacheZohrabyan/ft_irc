#include "../../../inc/administration/mode/topicMode.hpp"

TopicMode::TopicMode()
{

}

TopicMode::~TopicMode()
{

}

void TopicMode::executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message)
{
    (void)chanels;
    (void)message;
    (void)client;
    (void)fd;
}