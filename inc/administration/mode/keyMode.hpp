#pragma once

#include "AModeCommand.hpp"

class KeyMode : public AModeCommand
{
public:
    KeyMode();
    ~KeyMode();

public:
    void executeMode(Client& client, Chanel& chanels, int fd, const std::string& message, bool flag, const std::map<int, Client>& clients);

private:
    void addKey(Client& client, Chanel& chanel, bool flag, const std::string& message) const;
    void subKey(Client& client, Chanel& chanel, bool flag) const;
};