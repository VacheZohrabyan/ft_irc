#pragma once

#include "AModeCommand.hpp"

class LimitMode : public AModeCommand
{
public:
    LimitMode();
    ~LimitMode();

public:
    void executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message);
};