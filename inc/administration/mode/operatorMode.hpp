#pragma once

#include "AModeCommand.hpp"

class OperatorMode : public AModeCommand
{
public:
    OperatorMode();
    ~OperatorMode();

public:
    void executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message);
};