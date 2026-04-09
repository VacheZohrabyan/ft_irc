#pragma once

#include "AModeCommand.hpp"

class OperatorMode : public AModeCommand
{
public:
    OperatorMode();
    ~OperatorMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& chanelName, const std::string& message, bool flag);
};