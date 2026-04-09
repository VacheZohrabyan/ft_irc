#pragma once

#include "AModeCommand.hpp"

class LimitMode : public AModeCommand
{
public:
    LimitMode();
    ~LimitMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& chanelName, const std::string& message, bool flag);
};