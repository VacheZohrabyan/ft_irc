#pragma once

#include "AModeCommand.hpp"

class OperatorMode : public AModeCommand
{
public:
    OperatorMode();
    ~OperatorMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients);

private:
    bool findNick(const std::map<int, Client>& clients, const std::string& message) const;
    int getFd(const std::map<int, Client>& clients, const std::string& message) const;
};