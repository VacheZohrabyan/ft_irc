#pragma once

#include "AModeCommand.hpp"

class InviteMode : public AModeCommand
{
public:
    InviteMode();
    ~InviteMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients);
};