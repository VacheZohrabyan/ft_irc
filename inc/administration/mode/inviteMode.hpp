#pragma once

#include "AModeCommand.hpp"

class InviteMode : public AModeCommand
{
public:
    InviteMode();
    ~InviteMode();

public:
    void executeMode(Client& client, std::map<std::string, Chanel>& chanels, int fd, const std::string& message);
};