#pragma once

#include "AModeCommand.hpp"

class TopicMode : public AModeCommand
{
public:
    TopicMode();
    ~TopicMode();

public:
    void executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message);
};