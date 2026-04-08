#pragma once

#include "AModeCommand.hpp"

class KeyMode : public AModeCommand
{
public:
    KeyMode();
    ~KeyMode();

public:
    void executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message);
};