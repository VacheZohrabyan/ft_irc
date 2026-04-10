#pragma once

#include "AModeCommand.hpp"

class KeyMode : public AModeCommand
{
public:
    KeyMode();
    ~KeyMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag);
};