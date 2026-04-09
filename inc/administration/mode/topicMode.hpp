#pragma once

#include "AModeCommand.hpp"

class TopicMode : public AModeCommand
{
public:
    TopicMode();
    ~TopicMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& chanelName, const std::string& message, bool flag);
};